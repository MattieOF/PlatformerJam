// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "Core/HealthComponent.h"
#include "GameFramework/Character.h"
#include "PJBaseEnemy.generated.h"

class UEnemyData;
class UHealthComponent;

UCLASS()
class PLATFORMERJAM_API APJBaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APJBaseEnemy();
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetHealth() { return HealthComponent->GetHealth(); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void Hurt(float Amount) { HealthComponent->Damage(Amount); }

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static APJBaseEnemy* SpawnEnemy(UObject* WorldContextObject, UEnemyData* Data, FTransform Transform);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEnemyData* Data;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true))
	UHealthComponent* HealthComponent;
};
