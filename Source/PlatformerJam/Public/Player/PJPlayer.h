// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "PJPlayer.generated.h"

struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;

UCLASS()
class PLATFORMERJAM_API APJPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseMoveSpeed = 200;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseSens = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeedMultiplier = 1;
	
	// Sets default values for this character's properties
	APJPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE USpringArmComponent* GetBoom() const { return Boom; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static FORCEINLINE APJPlayer* GetPlayer(UObject* WorldContextObject)
	{
		return Cast<APJPlayer>(UGameplayStatics::GetPlayerPawn(WorldContextObject, 0));
	}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UPlayerMappableInputConfig* InputMappingConfig;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;

	void OnMove(const FInputActionValue& ActionValue);
	void OnJump(const FInputActionValue& ActionValue);
	void OnMouseLook(const FInputActionValue& ActionValue);

private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* Boom;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
};
