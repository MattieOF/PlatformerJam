// copyright lololol

#include "Weapon/Projectile/Projectile.h"

#include "PJLog.h"
#include "Enemy/PJBaseEnemy.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Projectile/ProjectileData.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	SetRootComponent(MeshComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetData(Data); // Call SetData to apply data
	MeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::SetData(UProjectileData* NewData)
{
	Data = NewData;
	if (Data)
	{
		if (Data->Mesh)
			MeshComponent->SetStaticMesh(Data->Mesh);
		MovementComponent->InitialSpeed = Data->Speed;
		MovementComponent->Velocity = GetActorRotation().Vector();
	}
}

AProjectile* AProjectile::SpawnProjectile(UObject* WorldContextObject, UProjectileData* Data, FVector Position,
	FVector Direction)
{
	if (!WorldContextObject)
	{
		PJ_LOG_ERROR("Attempted to spawn projectile with null world context object.");
		return nullptr;	
	}

	if (!Data)
	{
		PJ_LOG_ERROR("Attempted to spawn projectile with null data object.");
		return nullptr;
	}
	
	UWorld* World = WorldContextObject->GetWorld();
	
	if (!World)
	{
		PJ_LOG_ERROR("Attempted to spawn projectile with invalid world context object.");
		return nullptr;
	}

	const FTransform SpawnTransform = FTransform(Direction.ToOrientationRotator(), Position);
	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(Data->ProjectileClass, SpawnTransform);
	Projectile->Data = Data;
	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);

	return Projectile;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (APJBaseEnemy* Enemy = Cast<APJBaseEnemy>(OtherActor))
	{
		Enemy->Hurt(Data->Damage);
		// TODO: Reparent mesh to enemy
	}

	Destroy();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
