// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "ProjectileWeapon.generated.h"

class UProjectileData;

UCLASS()
class PLATFORMERJAM_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	AProjectileWeapon();

	virtual void Fire(bool bHeld) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProjectileData* ProjectileType;
};
