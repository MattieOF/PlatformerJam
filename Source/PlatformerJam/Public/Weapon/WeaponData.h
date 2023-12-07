// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

/**
 * Class for storing basic weapon data
 */
UCLASS()
class PLATFORMERJAM_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	FVector HeldOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	FRotator HeldOffsetRot;
	
	// Key used to identify which type of ammo this weapon uses. "None" means it's own, unique, and unnamed type.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
	FName AmmoTypeKey = "None";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
	bool bInfiniteAmmo = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
	bool bHasReserveAmmo = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
	int MaxClip = 20;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
	int MaxReserve = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functionality")
	bool bAutomatic = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functionality")
	float FireCooldown = 0.05f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functionality")
	int Slot = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functionality")
	TSubclassOf<AWeapon> WeaponClass;
};
