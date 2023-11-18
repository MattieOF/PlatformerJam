// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "PJPlayer.generated.h"

class UHealthComponent;
class FCTweenInstanceFloat;
struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFailDash);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSuccessfulDash, FVector, Direction);

UENUM(BlueprintType)
enum class EDashDirection : uint8
{
	Camera    UMETA(DisplayName = "Camera"),
	Movement  UMETA(DisplayName = "Movement")
};

UCLASS()
class PLATFORMERJAM_API APJPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Move Speed")
	float BaseMoveSpeed = 200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Move Speed")
	float AimingMoveSpeedMultiplier = 0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Move Speed")
	float MoveSpeedMultiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Dash")
	float DashChargeSpeed = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Dash")
	float DashStrength = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Dash")
	float DashFloatTime = 0.4f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Dash")
	bool bRechargeDashInAir = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats|Dash")
	EDashDirection DefaultDashDirection = EDashDirection::Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float HorizontalMouseSens = 200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float VerticalMouseSens = 80;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float AimingMouseSensMultiplier = 0.25f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	bool bInvertHorizontal = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	bool bInvertVertical = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FVector LeftCamOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FVector RightCamOffset;

	UPROPERTY(BlueprintReadOnly, Category = "Camera")
	float NormalArmLength = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float AimArmLength = 80;
	
	// Sets default values for this character's properties
	APJPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera")
	FORCEINLINE USpringArmComponent* GetBoom() const { return Boom; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera")
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetNormalArmLength(float NewLength);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player")
	FORCEINLINE bool IsAiming() const { return bIsAiming; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Player")
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
	UInputAction* DashAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SwitchSideAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AimAction;

	void OnMove(const FInputActionValue& ActionValue);
	void ClearMovementInput();
	void OnJump();
	void OnMouseLook(const FInputActionValue& ActionValue);
	void OnSwitchSide();
	void OnAim(const FInputActionValue& ActionValue);
	void OnDash();

	UPROPERTY(BlueprintReadOnly)
	bool bCamOnLeft = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsAiming = false;

	UPROPERTY(BlueprintReadOnly)
	float DashCharge = 1;
	UPROPERTY(BlueprintReadOnly)
	float FloatingTime = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* Boom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHealthComponent* Health;

	UPROPERTY(BlueprintAssignable)
	FOnFailDash OnFailDash;
	
	UPROPERTY(BlueprintAssignable)
	FOnSuccessfulDash OnSuccessfulDash;
	
private:
	FCTweenInstanceFloat* AimingTween;

	FVector2D CurrentMovementInput;
};
