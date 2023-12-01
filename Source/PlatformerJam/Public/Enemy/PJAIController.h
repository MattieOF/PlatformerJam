// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PJAIController.generated.h"

class UEnemyData;

UCLASS()
class PLATFORMERJAM_API APJAIController : public AAIController
{
	GENERATED_BODY()

public:
	APJAIController();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetEnemyData(UEnemyData* NewData);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UEnemyData* Data;
};
