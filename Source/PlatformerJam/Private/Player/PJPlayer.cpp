// copyright lololol

#include "Player/PJPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "PJLog.h"
#include "PlayerMappableInputConfig.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APJPlayer::APJPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Boom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
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
	FVector2D Input = ActionValue.Get<FVector2D>();
	if (Input == FVector2D::ZeroVector) return;

	Input = Input.GetSafeNormal();
	FRotator LookYaw = FRotator(0, GetControlRotation().Yaw, 0);
	
	FVector LookDir = FRotationMatrix(LookYaw).GetUnitAxis(EAxis::X);
	AddMovementInput(LookDir * Input.X,
	                 BaseMoveSpeed * MoveSpeedMultiplier * GetWorld()->DeltaTimeSeconds, false);
	LookDir = FRotationMatrix(LookYaw).GetUnitAxis(EAxis::Y);
	AddMovementInput(LookDir * Input.Y,
					 BaseMoveSpeed * MoveSpeedMultiplier * GetWorld()->DeltaTimeSeconds, false);
}

void APJPlayer::OnJump(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		Jump();
	}
}

void APJPlayer::OnMouseLook(const FInputActionValue& ActionValue)
{
	const FVector2D Input = ActionValue.Get<FVector2D>();
	UE_LOG(LogPJ, Log, TEXT("Mouse: %s"), *Input.ToString());
	AddControllerYawInput(Input.X * GetWorld()->DeltaTimeSeconds * MouseSens);
	AddControllerPitchInput(Input.Y * GetWorld()->DeltaTimeSeconds * MouseSens);
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
		EnhancedInputComponent->BindAction(MoveAction,      ETriggerEvent::Triggered, this, &APJPlayer::OnMove);
		EnhancedInputComponent->BindAction(JumpAction,      ETriggerEvent::Triggered, this, &APJPlayer::OnJump);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APJPlayer::OnMouseLook);
	}
}
