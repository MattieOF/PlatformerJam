// copyright lololol

#include "Weapon/Weapon.h"

#include "PJLog.h"
#include "Player/PJPlayer.h"
#include "Weapon/WeaponData.h"

AWeapon::AWeapon()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	PrimaryActorTick.bCanEverTick = true;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	SetData(Data); // Call set function to apply data
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::SetData(UWeaponData* NewData)
{
	Data = NewData;
	if (ClipAmmo == -1)
		ClipAmmo = Data->MaxClip;
}

void AWeapon::SetClipAmmo(int NewClip)
{
	ClipAmmo = NewClip;
}

void AWeapon::Equip()
{
	Mesh->SetVisibility(true);
}

void AWeapon::Unequip()
{
	Mesh->SetVisibility(false);
}

void AWeapon::Fire()
{
	UE_LOG(LogPJ, Error, TEXT("Base weapon fire function called by %s!"), *GetName());
}

AWeapon* AWeapon::SpawnWeapon(UWeaponData* Data, APJPlayer* Player, UObject* WorldContextObject, int SpawnClip)
{
	if (!Data->WeaponClass.Get())
	{
		UE_LOG(LogPJ, Error, TEXT("Tried to spawn weapon with invalid class (from data of %s)"), *Data->Name.ToString());
		return nullptr;
	}
	
	AWeapon* Weapon = WorldContextObject->GetWorld()->SpawnActorDeferred<AWeapon>(
		Data->WeaponClass, Player->GetTransform(), Player);
	Weapon->Data = Data;
	Weapon->Player = Player;
	UGameplayStatics::FinishSpawningActor(Weapon, Player->GetTransform());
	
	return Weapon;
}
