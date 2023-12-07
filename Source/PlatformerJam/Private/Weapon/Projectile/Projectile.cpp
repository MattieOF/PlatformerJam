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
	RootComponent = MeshComponent;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (APJBaseEnemy* Enemy = Cast<APJBaseEnemy>(OtherActor))
	{
		Enemy->Hurt(Data->Damage);
		OnHitEnemy.Broadcast(Enemy, Hit.ImpactPoint, MovementComponent->Velocity.GetSafeNormal());
	} else
		OnHitElsewhere.Broadcast(OtherActor, Hit.ImpactPoint, MovementComponent->Velocity.GetSafeNormal());
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetData(Data);
	MeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::SetData(UProjectileData* NewData)
{
	Data = NewData;

	if (!Data)
	{
		PJ_LOG_ERROR(FString::Printf(TEXT("In projectile %s, SetData() called with null data!"), *GetName()));
		return;
	}

	if (Data->Mesh)
		MeshComponent->SetStaticMesh(Data->Mesh);

	MovementComponent->Velocity = Direction * Data->Speed;
}

AProjectile* AProjectile::SpawnProjectile(UObject* WorldContextObject, UProjectileData* Data, FVector Position,
	FVector Direction)
{
	// Do extra debugging checks in editor only
#ifdef WITH_EDITOR
	if (!WorldContextObject)
	{
		PJ_LOG_ERROR("In SpawnProjectile(), null world context object provided!");
		return nullptr;
	}

	if (!Data)
	{
		PJ_LOG_ERROR("In SpawnProjectile(), null data provided!");
		return nullptr;
	}

	if (!Data->ProjectileClass.Get())
	{
		PJ_LOG_ERROR("In SpawnProjectile(), data with null projectile class provided!");
		return nullptr;
	}
#endif

	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		PJ_LOG_ERROR("In SpawnProjectile(), invalid world context object provided!");
		return nullptr;
	}

	const FTransform SpawnTransform(Position);
	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(Data->ProjectileClass, SpawnTransform);
	Projectile->Direction = Direction;
	Projectile->Data = Data;
	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	
	return Projectile;
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
