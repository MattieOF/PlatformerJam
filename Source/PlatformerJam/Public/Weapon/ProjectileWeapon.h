// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "ProjectileWeapon.generated.h"

UCLASS()
class PLATFORMERJAM_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileWeapon();

	virtual void Fire(const bool bHeld) override;
};
