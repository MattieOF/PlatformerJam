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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float BaseMoveSpeed = 200;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float MoveSpeedMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float HorizontalMouseSens = 200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float VerticalMouseSens = 80;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	bool bInvertHorizontal = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	bool bInvertVertical = false;

	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector LeftCamOffset;
	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector RightCamOffset;
	
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
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SwitchSideAction;

	void OnMove(const FInputActionValue& ActionValue);
	void OnJump();
	void OnMouseLook(const FInputActionValue& ActionValue);
	void OnSwitchSide();

	bool bCamOnLeft = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* Boom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;
};
