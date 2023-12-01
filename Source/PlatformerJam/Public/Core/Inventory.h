// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Inventory.generated.h"

class AWeapon;
/**
 * Object that stores items and ammo for an actor
 */
UCLASS()
class PLATFORMERJAM_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ammo")
	int GetAmmo(FName Type);
	
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	bool CanUse(FName Type, int Required, bool Take = true);
	
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	int AddAmmo(FName Type, int Amount);
	
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	int UseAmmo(FName Type, int Amount);

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	int UseAmountOrLess(FName Type, int DesiredAmount);

private:
	TMap<int, AWeapon*> Weapons;
	TMap<FName, int> Ammo;
};
