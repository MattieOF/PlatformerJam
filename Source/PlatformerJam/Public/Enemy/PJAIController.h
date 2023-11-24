// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PJAIController.generated.h"

UCLASS()
class PLATFORMERJAM_API APJAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APJAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
