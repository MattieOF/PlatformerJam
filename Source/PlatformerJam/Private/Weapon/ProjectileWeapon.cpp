// copyright lololol

#include "Weapon/ProjectileWeapon.h"

#include "PJLog.h"
#include "Weapon/WeaponData.h"

// Sets default values
AProjectileWeapon::AProjectileWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectileWeapon::Fire(bool bHeld)
{
	if (!CanFire(bHeld))
		return;

	UE_LOG(LogPJ, Log, TEXT("Fire!!"));

	FiringCooldown = Data->FireCooldown;
}
