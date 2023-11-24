// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealed, float, NewHealth, float, HealAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHurt, float, NewHealth, float, HurtAmount);

UCLASS(ClassGroup=(PJ), meta=(BlueprintSpawnableComponent))
class PLATFORMERJAM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool AllowsOverheal() const { return bAllowOverheal; }
	UFUNCTION(BlueprintCallable)
	void SetAllowsOverheal(bool bNewValue, bool bClampHealth = true);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool AllowsNegative() const { return bAllowNegative; }
	UFUNCTION(BlueprintCallable)
	void SetAllowsNegative(bool bNewValue, bool bClampHealth = true);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetHealth() const { return CurrentHealth; }
	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHealth);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float NewMaxHealth, bool bClampHealth = true);

	UFUNCTION(BlueprintCallable)
	void Damage(float Amount);
	UFUNCTION(BlueprintCallable)
	void Heal(float Amount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OverhealDecayRate = 5;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnHealed OnHealed;
	UPROPERTY(BlueprintAssignable)
	FOnHurt OnHurt;
	
protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAllowOverheal = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAllowNegative = false;
};
