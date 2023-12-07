// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gibs.generated.h"

UCLASS()
class PLATFORMERJAM_API AGibs : public AActor
{
	GENERATED_BODY()

public:
	AGibs();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<USceneComponent*> Gibs;

	bool Alive = true;
	float ElapsedTime = 0;
	
	UPROPERTY(EditAnywhere)
	FVector2f FadeOutRange = FVector2f(5, 8);
};
