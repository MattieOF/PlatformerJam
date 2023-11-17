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
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APJPlayer::APJPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called when the game starts or when spawned
void APJPlayer::BeginPlay()
{
	NormalArmLength = Boom->TargetArmLength;
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
	FVector2D Input = ActionValue.Get<FVector2D>();
	// if (Input == FVector2D::ZeroVector) return; // Removed for now; func shouldn't be called if input is 0
	Input = Input.GetSafeNormal();
	
	FRotator LookYaw = FRotator(0, GetControlRotation().Yaw, 0);

	const float AimingSlowdownMultiplier = bIsAiming ? AimingMoveSpeedMultiplier : 1;
	FVector LookDir = FRotationMatrix(LookYaw).GetUnitAxis(EAxis::X);
	AddMovementInput(LookDir * (Input.X * (bInvertHorizontal ? -1 : 1)),
	                 BaseMoveSpeed * MoveSpeedMultiplier * AimingSlowdownMultiplier * GetWorld()->DeltaTimeSeconds, false);
	LookDir = FRotationMatrix(LookYaw).GetUnitAxis(EAxis::Y);
	AddMovementInput(LookDir * (Input.Y * (bInvertVertical ? -1 : 1)),
					 BaseMoveSpeed * MoveSpeedMultiplier * AimingSlowdownMultiplier * GetWorld()->DeltaTimeSeconds, false);
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
}

// Called every frame
void APJPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APJPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,       ETriggerEvent::Triggered, this, &APJPlayer::OnMove);
		EnhancedInputComponent->BindAction(JumpAction,       ETriggerEvent::Triggered, this, &APJPlayer::OnJump);
		EnhancedInputComponent->BindAction(MouseLookAction,  ETriggerEvent::Triggered, this, &APJPlayer::OnMouseLook);
		EnhancedInputComponent->BindAction(SwitchSideAction, ETriggerEvent::Triggered, this, &APJPlayer::OnSwitchSide);
		EnhancedInputComponent->BindAction(AimAction,        ETriggerEvent::Triggered, this, &APJPlayer::OnAim);
	}
}

void APJPlayer::SetNormalArmLength(float NewLength)
{
	NormalArmLength = NewLength;
	if (!bIsAiming)
		Boom->TargetArmLength = NewLength;
}
