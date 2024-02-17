// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UProjectileData;

UCLASS()
class PLATFORMERJAM_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UProjectileData* GetData() const { return Data; }

	UFUNCTION(BlueprintCallable)
	void SetData(UProjectileData* NewData);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static AProjectile* SpawnProjectile(UObject* WorldContextObject, UProjectileData* Data, FVector Position, FVector Direction);

	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProjectileData* Data = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComponent;
};
