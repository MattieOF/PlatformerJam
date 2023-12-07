// copyright lololol

#include "Weapon/ProjectileWeapon.h"

#include "PJLog.h"
#include "Player/PJPlayer.h"
#include "Weapon/WeaponData.h"
#include "Weapon/Projectile/Projectile.h"

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

	FVector ProjPoint = Mesh->GetSocketLocation("ProjectilePoint");
	AProjectile::SpawnProjectile(this, ProjectileType, ProjPoint, Player->GetAimDirectionFromOrigin(ProjPoint));

	FiringCooldown = Data->FireCooldown;
}
