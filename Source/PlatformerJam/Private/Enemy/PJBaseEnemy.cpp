// copyright lololol

#include "Enemy/PJBaseEnemy.h"

#include "PJLog.h"

#include "Enemy/EnemyData.h"
#include "Enemy/Gibs.h"
#include "Enemy/PJAIController.h"
#include "Enemy/PJEnemyAnimInstance.h"

APJBaseEnemy::APJBaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void APJBaseEnemy::OnDeath()
{
	const FTransform TF = GetActorTransform();
	GetWorld()->SpawnActor(Data->GibsClass, &TF);
	Destroy();
}

void APJBaseEnemy::BeginPlay()
{
	if (!Data)
	{
		PJ_LOG_ERROR(FString::Printf(TEXT("In enemy %s, null EnemyData! Destroying self."), *GetName()));
		Destroy();
		return;
	}
	
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

	if (Data->DefaultMesh)
	{
		GetMesh()->SetSkeletalMesh(Data->DefaultMesh);
	}
	
	if (Data->AnimationBlueprint.Get())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->AnimClass = Data->AnimationBlueprint;
	}
	
	HealthComponent->SetMaxHealth(Data->MaxHP);
	HealthComponent->OnDeath.AddDynamic(this, &APJBaseEnemy::OnDeath);
	
	Super::BeginPlay();
}

void APJBaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
