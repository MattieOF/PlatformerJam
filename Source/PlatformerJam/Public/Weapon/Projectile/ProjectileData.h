// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileData.generated.h"

class AProjectile;
/**
 * Class for storing basic details about a projectile.
 */
UCLASS()
class PLATFORMERJAM_API UProjectileData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	FText Name = FText::FromString("Projectile");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Functionality")
	TSubclassOf<AProjectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Speed = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Damage = 10;
};
