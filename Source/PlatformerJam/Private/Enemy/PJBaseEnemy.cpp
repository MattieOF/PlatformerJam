// copyright lololol

#include "Enemy/PJBaseEnemy.h"

#include "PJLog.h"
#include "Enemy/EnemyData.h"
#include "Kismet/GameplayStatics.h"

APJBaseEnemy::APJBaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

APJBaseEnemy* APJBaseEnemy::SpawnEnemy(UObject* WorldContextObject, UEnemyData* Data, FTransform Transform)
{
	if (!WorldContextObject)
	{
		PJ_LOG_ERROR("Attempted to spawn enemy with null world context object.");
		return nullptr;	
	}

	if (!Data)
	{
		PJ_LOG_ERROR("Attempted to spawn enemy with null data object.");
		return nullptr;
	}
	
	UWorld* World = WorldContextObject->GetWorld();
	
	if (!World)
	{
		PJ_LOG_ERROR("Attempted to spawn enemy with invalid world context object.");
		return nullptr;
	}

	APJBaseEnemy* Enemy = World->SpawnActorDeferred<APJBaseEnemy>(Data->EnemyClass, Transform);
	Enemy->Data = Data;
	UGameplayStatics::FinishSpawningActor(Enemy, Transform);

	return Enemy;
}

void APJBaseEnemy::BeginPlay()
{
	// Initialise components with data
	if (Controller)
	{
		Controller->Destroy();
		Controller = nullptr;
	}
	
	AIControllerClass = Data->AIControllerClass;
	SpawnDefaultController();
	
	if (APJAIController* PJAI = Cast<APJAIController>(GetController()))
	{
		PJAI->SetEnemyData(Data);
	} else
	{
		PJ_LOG_ERROR(FString::Printf(TEXT("In AI %s with EnemyData %s, using non PJAIController!"), *GetName(), *Data->GetName()));
	}

	if (Data->DefaultMesh)
		GetMesh()->SetSkeletalMesh(Data->DefaultMesh);
	
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
