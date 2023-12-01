// copyright lololol

#include "Enemy/PJAIController.h"

#include "Enemy/EnemyData.h"

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

void APJAIController::SetEnemyData(UEnemyData* NewData)
{
	Data = NewData;
	
	if (Data->Blackboard && Data->BehaviorTree)
	{
		// Run BB and BT if it's set
		auto BlackboardPointer = Blackboard.Get();
		UseBlackboard(Data->Blackboard, BlackboardPointer);
		Blackboard = BlackboardPointer;
		RunBehaviorTree(Data->BehaviorTree);
	}
}
