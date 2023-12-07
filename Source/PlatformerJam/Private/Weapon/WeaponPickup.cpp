// copyright lololol

#include "Weapon/WeaponPickup.h"

#include "PJLog.h"
#include "Components/BoxComponent.h"
#include "Core/Inventory.h"
#include "Player/PJPlayer.h"
#include "Weapon/Weapon.h"
#include "Weapon/WeaponData.h"

AWeaponPickup::AWeaponPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetMobility(EComponentMobility::Movable);
	MeshComponent->SetSimulatePhysics(true);
	PickupRange = CreateDefaultSubobject<UBoxComponent>(TEXT("Pickup Range"));
	PickupRange->SetupAttachment(MeshComponent);
	RootComponent = MeshComponent;
}

void AWeaponPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APJPlayer* Player = Cast<APJPlayer>(OtherActor))
	{
		AWeapon* Weapon = AWeapon::SpawnWeapon(WeaponData, Player, this);
		Player->GetInventory()->GiveWeapon(Weapon);
		Player->SelectWeaponSlot(Weapon->GetData()->Slot); // TODO: Priority system?
		Destroy();
	}
}

void AWeaponPickup::BeginPlay()
{
	if (!WeaponData)
	{
		PJ_LOG_ERROR(FString::Printf(TEXT("In weapon pickup %s, null WeaponData! Destroying self."), *GetName()));
		Destroy();
		return;
	}
	
	Super::BeginPlay();
	MeshComponent->SetStaticMesh(WeaponData->Mesh);
	PickupRange->SetWorldLocation(MeshComponent->Bounds.Origin);
	PickupRange->SetBoxExtent(MeshComponent->Bounds.BoxExtent * 2);
	PickupRange->OnComponentBeginOverlap.AddDynamic(this, &AWeaponPickup::OnOverlap);
}
