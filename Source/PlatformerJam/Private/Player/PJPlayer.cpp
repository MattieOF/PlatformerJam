// copyright lololol

#include "Player/PJPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FCTween.h"
#include "InputMappingContext.h"
#include "PJLog.h"
#include "PlayerMappableInputConfig.h"
#include "Camera/CameraComponent.h"
#include "Core/HealthComponent.h"
#include "Core/Inventory.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/Weapon.h"

// Sets default values
APJPlayer::APJPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory")); 
	Boom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Camera->SetupAttachment(Boom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Boom->SetupAttachment(RootComponent);

	Boom->bEnableCameraLag = true;
	Boom->CameraLagSpeed = 3.0f;
	// Boom->SetUsingAbsoluteRotation(true);
	Boom->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = false;
	JumpMaxCount = 2;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APJPlayer::SelectWeaponSlot(int Slot)
{
	if (AWeapon* Weapon = Inventory->GetWeaponInSlot(Slot))
	{
		if (CurrentWeapon)
			CurrentWeapon->Unequip();

		CurrentWeapon = Weapon;
		CurrentWeapon->Equip();
		OnEquipWeapon.Broadcast(CurrentWeapon, Slot);
	} else
	{
		OnFailedToEquipWeapon.Broadcast(Slot);
	}
}

// Called when the game starts or when spawned
void APJPlayer::BeginPlay()
{
	NormalGravity = GetCharacterMovement()->GravityScale;
	NormalArmLength = Boom->TargetArmLength;
	DefaultMeshRot = GetMesh()->GetRelativeRotation();
	Super::BeginPlay();
}

void APJPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	const APlayerController* const PlayerController = Cast<APlayerController>(NewController);
	if (!PlayerController)
	{
		UE_LOG(LogPJ, Warning, TEXT("PJPlayer possessed by non PlayerController!"));
		return;
	}

	// Register input
	if (const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingConfig)
				InputSystem->AddPlayerMappableConfig(InputMappingConfig);
		}
	}
}

void APJPlayer::OnMove(const FInputActionValue& ActionValue)
{
	// Get and normalise movement input
	CurrentMovementInput = ActionValue.Get<FVector2D>();
	// if (Input == FVector2D::ZeroVector) return; // Removed for now; func shouldn't be called if input is 0
	CurrentMovementInput = CurrentMovementInput.GetSafeNormal();

	const FRotator LookYaw = FRotator(0, GetControlRotation().Yaw, 0);

	const float AimingSlowdownMultiplier = bIsAiming ? AimingMoveSpeedMultiplier : 1;
	FVector LookDir = FRotationMatrix(LookYaw).GetUnitAxis(EAxis::X);
	AddMovementInput(LookDir * (CurrentMovementInput.X * (bInvertHorizontal ? -1 : 1)),
	                 BaseMoveSpeed * MoveSpeedMultiplier * AimingSlowdownMultiplier * GetWorld()->DeltaTimeSeconds, false);
	LookDir = FRotationMatrix(LookYaw).GetUnitAxis(EAxis::Y);
	AddMovementInput(LookDir * (CurrentMovementInput.Y * (bInvertVertical ? -1 : 1)),
					 BaseMoveSpeed * MoveSpeedMultiplier * AimingSlowdownMultiplier * GetWorld()->DeltaTimeSeconds, false);
}

void APJPlayer::ClearMovementInput()
{
	CurrentMovementInput = FVector2D::ZeroVector;
}

void APJPlayer::OnJump()
{
	Jump();
}

void APJPlayer::OnMouseLook(const FInputActionValue& ActionValue)
{
	const float AimingSpeedMultiplier = bIsAiming ? AimingMouseSensMultiplier : 1;
	const FVector2D Input = ActionValue.Get<FVector2D>();
	AddControllerYawInput(Input.X * GetWorld()->DeltaTimeSeconds * HorizontalMouseSens * AimingSpeedMultiplier);
	AddControllerPitchInput(Input.Y * GetWorld()->DeltaTimeSeconds * VerticalMouseSens * AimingSpeedMultiplier);
}

void APJPlayer::OnSwitchSide()
{
	FCTween::Play(Camera->GetRelativeLocation(), bCamOnLeft ? LeftCamOffset : RightCamOffset,
	              [this](FVector Vector) { Camera->SetRelativeLocation(Vector); }, 0.3f, EFCEase::OutExpo);
	bCamOnLeft = !bCamOnLeft;
}

void APJPlayer::OnAim(const FInputActionValue& ActionValue)
{
	// Check our new state and return if we're already in it
	const bool bIsButtonHeld = ActionValue.Get<bool>();
	if (bIsAiming == bIsButtonHeld) return;

	// Ensure aiming tween isn't currently active
	if (AimingTween && AimingTween->bIsActive)
		AimingTween->Destroy();

	// Do aiming tween
	AimingTween = FCTween::Play(Boom->TargetArmLength, bIsButtonHeld ? AimArmLength : NormalArmLength,
	                            [this](float ArmLength) { Boom->TargetArmLength = ArmLength; }, 0.3f, EFCEase::OutExpo);
	
	// Set new state
	bIsAiming = bIsButtonHeld;
	GetCharacterMovement()->bOrientRotationToMovement = !bIsAiming;
	if (!bIsAiming)
		GetMesh()->SetRelativeRotation(DefaultMeshRot);
}

void APJPlayer::OnFire(bool bHeld)
{
	if (!bIsAiming || !CurrentWeapon)
		return;
	
	UE_LOG(LogPJ, Log, TEXT("Firing (held: %hs)"), bHeld ? "True" : "False");

	CurrentWeapon->Fire(bHeld);
}

void APJPlayer::OnDash()
{
	// Check we have enough charge
	// If not, send a delegate so cosmetic things can happen
	if (DashCharge < 1)
	{
		OnFailDash.Broadcast();
		return;
	}

	// Perform the dash
	FVector Dir;
	const FRotator Rot = FRotator(0, GetControlRotation().Yaw, 0);
	if (DefaultDashDirection == EDashDirection::Camera || CurrentMovementInput.IsZero())
		Dir = Rot.Vector();
	else
		Dir = FRotationMatrix(Rot).TransformVector(FVector(CurrentMovementInput, 0));
	GetCharacterMovement()->Velocity = Dir * DashStrength;
	OnSuccessfulDash.Broadcast(Dir);

	FloatingTime = DashFloatTime;
	
	// Reset dash charge to 0
	DashCharge = 0;
}

// Called every frame
void APJPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Regenerate dash
	if (DashCharge < 1 && (bRechargeDashInAir || GetCharacterMovement()->IsMovingOnGround()))
		DashCharge = FMath::Min(1, DashCharge + (DeltaTime * DashChargeSpeed));

	if (FloatingTime > 0)
	{
		GetCharacterMovement()->GravityScale = 0;
		FloatingTime = FMath::Max(0, FloatingTime - DeltaTime);
	}
	else
		GetCharacterMovement()->GravityScale = NormalGravity;

	if (bIsAiming)
	{
		FRotator Rot = Camera->GetComponentRotation();
		Rot.Roll = 0;
		Rot.Pitch = 0;
		Rot.Yaw -= 90;
		GetMesh()->SetWorldRotation(Rot);
	}
}

// Called to bind functionality to input
void APJPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,       ETriggerEvent::Triggered, this, &APJPlayer::OnMove);
		EnhancedInputComponent->BindAction(JumpAction,       ETriggerEvent::Triggered, this, &APJPlayer::OnJump);
		EnhancedInputComponent->BindAction(DashAction,       ETriggerEvent::Triggered, this, &APJPlayer::OnDash);
		EnhancedInputComponent->BindAction(MouseLookAction,  ETriggerEvent::Triggered, this, &APJPlayer::OnMouseLook);
		EnhancedInputComponent->BindAction(SwitchSideAction, ETriggerEvent::Triggered, this, &APJPlayer::OnSwitchSide);
		EnhancedInputComponent->BindAction(AimAction,        ETriggerEvent::Triggered, this, &APJPlayer::OnAim);
		
		EnhancedInputComponent->BindAction(FireAction,       ETriggerEvent::Started,   this, &APJPlayer::OnFire, false);
		EnhancedInputComponent->BindAction(FireAction,       ETriggerEvent::Triggered, this, &APJPlayer::OnFire, true);

		// Bind weapon slot inputs
		EnhancedInputComponent->BindAction(WeaponSlot1Action, ETriggerEvent::Triggered, this, &APJPlayer::SelectWeaponSlot, 1);
		EnhancedInputComponent->BindAction(WeaponSlot2Action, ETriggerEvent::Triggered, this, &APJPlayer::SelectWeaponSlot, 2);
		EnhancedInputComponent->BindAction(WeaponSlot3Action, ETriggerEvent::Triggered, this, &APJPlayer::SelectWeaponSlot, 3);
		EnhancedInputComponent->BindAction(WeaponSlot4Action, ETriggerEvent::Triggered, this, &APJPlayer::SelectWeaponSlot, 4);
		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::None, this, &APJPlayer::ClearMovementInput);
	}
}

void APJPlayer::SetNormalArmLength(float NewLength)
{
	NormalArmLength = NewLength;
	if (!bIsAiming)
		Boom->TargetArmLength = NewLength;
}

FVector APJPlayer::GetAimDirection() const
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.bTraceComplex = true;
	CollisionQueryParams.AddIgnoredActor(this);
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + Camera->GetForwardVector() * 1000;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionQueryParams);
	End = bHit ? HitResult.ImpactPoint : End;
	return (End - Start).GetSafeNormal();
}
