// copyright lololol

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "EnemyData.generated.h"

class AGibs;
class UBlackboardData;
class UBehaviorTree;
class UPJEnemyAnimInstance;
class APJAIController;
class APJBaseEnemy;

/**
 * Data for an enemy
 */
UCLASS()
class PLATFORMERJAM_API UEnemyData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functionality")
	TSubclassOf<APJBaseEnemy> EnemyClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functionality")
	TSubclassOf<APJAIController> AIControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functionality")
	UBlackboardData* Blackboard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functionality")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	USkeletalMesh* DefaultMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TSubclassOf<UPJEnemyAnimInstance> AnimationBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TSubclassOf<AGibs> GibsClass;
};
