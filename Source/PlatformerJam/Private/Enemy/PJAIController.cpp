// copyright lololol

#include "Enemy/PJAIController.h"

// Sets default values
APJAIController::APJAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APJAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APJAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

