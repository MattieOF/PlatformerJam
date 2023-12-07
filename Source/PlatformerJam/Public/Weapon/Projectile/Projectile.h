// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "ProjectileData.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class APJBaseEnemy;
class UProjectileData;
class UProjectileMovementComponent;

UCLASS()
class PLATFORMERJAM_API AProjectile : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHitEnemy, APJBaseEnemy*, Enemy, FVector, Position, FVector, Direction);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHitElsewhere, AActor*, Actor, FVector, Position, FVector, Direction);

public:
	AProjectile();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UProjectileData* GetData() const { return Data; }
	
	UFUNCTION(BlueprintCallable)
	void SetData(UProjectileData* NewData);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static AProjectile* SpawnProjectile(UObject* WorldContextObject, UProjectileData* Data, FVector Position, FVector Direction);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;

	UPROPERTY(BlueprintAssignable)
	FOnHitEnemy OnHitEnemy;
	
	UPROPERTY(BlueprintAssignable)
	FOnHitElsewhere OnHitElsewhere;
	
protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProjectileData* Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;
};
