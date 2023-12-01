// copyright lololol

#pragma once

#include "CoreMinimal.h"

#include "PJEnemyAnimInstance.h"
#include "PJAIController.h" // I don't like having to include these here; feels like a circ dependency waiting to happen.
							// However, TSubclassOf needs to have the definitions included to work.

#include "Engine/DataAsset.h"
#include "EnemyData.generated.h"

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
	TSubclassOf<APJAIController> AIControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functionality")
	UBlackboardData* Blackboard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functionality")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	USkeletalMesh* DefaultMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TSubclassOf<UPJEnemyAnimInstance> AnimationBlueprint;
};
