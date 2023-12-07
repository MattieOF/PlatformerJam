// copyright lololol

#include "Core/Inventory.h"

#include "PJLog.h"
#include "Weapon/Weapon.h"
#include "Weapon/WeaponData.h"

int UInventory::GetAmmo(FName Type)
{
	if (Ammo.Contains(Type))
		return Ammo[Type];

	return -1;
}

bool UInventory::CanUse(FName Type, int Required, bool Take)
{
	if (GetAmmo(Type) < Required)
		return false;

	if (Take)
		UseAmmo(Type, Required);
	
	return true;
}

int UInventory::AddAmmo(FName Type, int Amount)
{
	if (Ammo.Contains(Type))
		Ammo[Type] += Amount;
	else
		Ammo.Add(Type, Amount);

	return Ammo[Type];
}

int UInventory::UseAmmo(FName Type, int Amount)
{
	if (!Ammo.Contains(Type))
		return -1;

	Ammo[Type] -= Amount;
	if (Ammo[Type] <= 0)
	{
		Ammo.Remove(Type);
		return -1;
	}
	
	return Ammo[Type];
}

int UInventory::UseAmountOrLess(FName Type, int DesiredAmount)
{
	if (!Ammo.Contains(Type))
		return 0;

	const int Used = FMath::Min(Ammo[Type], DesiredAmount);
	
	Ammo[Type] -= Used;
	if(Ammo[Type] <= 0)
		Ammo.Remove(Type);
	
	return Used;
}

AWeapon* UInventory::GetWeaponInSlot(const int Slot) const
{
	if (Weapons.Contains(Slot))
		return Weapons[Slot];
	return nullptr;
}

bool UInventory::GiveWeapon(AWeapon* Weapon, const int Ammo)
{
	if (!Weapon)
	{
		PJ_LOG_ERROR("Inventory attempted to receive null weapon!");
		return false;
	}

	if (Ammo != 0)
		AddAmmo(Weapon->GetData()->AmmoTypeKey, Ammo == -1 ? Weapon->GetData()->MaxClip : Ammo);
	
	if (!Weapons.Contains(Weapon->GetData()->Slot))
	{
		Weapons.Add(Weapon->GetData()->Slot, Weapon);
		return true;
	}

	return false;
}
