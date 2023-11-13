// copyright lololol

#include "Player/PJPlayer.h"

#include "PJLog.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APJPlayer::APJPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Boom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Boom);
	Boom->SetupAttachment(RootComponent);

	Boom->bEnableCameraLag = true;
	Boom->CameraLagSpeed = 3.0f;
	
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

	// APlayerController* const PlayerController = Cast<APlayerController>(NewController);
	// if (!PlayerController)
	// {
	// 	UE_LOG(LogPJ, Warning, TEXT("PJPlayer possessed by non PlayerController!"));
	// 	return;
	// }
	// PlayerController->SetViewTarget(this);
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
}
