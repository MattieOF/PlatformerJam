// copyright lololol

#include "Weapon/Weapon.h"

#include "PJLog.h"
#include "Player/PJPlayer.h"
#include "Weapon/WeaponData.h"

AWeapon::AWeapon()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = Mesh;
	
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

	if (FiringCooldown > 0)
		FiringCooldown = FMath::Max(0, FiringCooldown - DeltaTime);
}

void AWeapon::SetData(UWeaponData* NewData)
{
	Data = NewData;
	Mesh->SetStaticMesh(Data->Mesh);
	if (ClipAmmo == -1)
		ClipAmmo = Data->MaxClip;
}

void AWeapon::SetClipAmmo(int NewClip)
{
	ClipAmmo = NewClip;
}

void AWeapon::Equip()
{
	Mesh->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponHandSocket");
	Mesh->SetRelativeLocation(Data->HeldOffset);
	Mesh->SetRelativeRotation(Data->HeldOffsetRot);
	Mesh->SetVisibility(true);
}

void AWeapon::Unequip()
{
	Mesh->SetVisibility(false);
}

bool AWeapon::CanFire(bool bHeld)
{
	return FiringCooldown <= 0 && (!bHeld || Data->bAutomatic) && ClipAmmo > 0;
}

void AWeapon::Fire(bool bHeld)
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
