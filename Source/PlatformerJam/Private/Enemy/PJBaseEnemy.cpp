// copyright lololol

#include "Enemy/PJBaseEnemy.h"

#include "PJLog.h"
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

	// Init AI controller
	AIControllerClass = Data->AIControllerClass;
	if (Controller)
	{
		Controller->Destroy();
		Controller = nullptr;
	}
	SpawnDefaultController();

	if (APJAIController* PJAI = Cast<APJAIController>(GetController()))
	{
		PJAI->SetEnemyData(Data);
	} else
	{
		PJ_LOG_ERROR(FString::Printf(TEXT("In AI %s with EnemyData %s, using non PJAIController!"), *GetName(), *Data->GetName()));
	}
	
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
