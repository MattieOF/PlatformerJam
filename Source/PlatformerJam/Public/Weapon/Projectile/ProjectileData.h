// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileData.generated.h"

class AProjectile;

/**
 * Class that stores projectile data
 */
UCLASS()
class PLATFORMERJAM_API UProjectileData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AProjectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Damage;
};
