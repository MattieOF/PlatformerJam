// copyright lololol

#include "Enemy/PJBaseEnemy.h"

#include "Enemy/EnemyData.h"

APJBaseEnemy::APJBaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void APJBaseEnemy::BeginPlay()
{
	// Initialise components with data
	AIControllerClass = Data->AIControllerClass;
	
	if (Data->AnimationBlueprint.Get())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->AnimClass = Data->AnimationBlueprint;
	}
	
	HealthComponent->SetMaxHealth(Data->MaxHP);
	
	Super::BeginPlay();
}

void APJBaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
