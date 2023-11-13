// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PJPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PLATFORMERJAM_API APJPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APJPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE USpringArmComponent* GetBoom() { return Boom; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UCameraComponent* GetCamera() { return Camera; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* Boom;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
};
