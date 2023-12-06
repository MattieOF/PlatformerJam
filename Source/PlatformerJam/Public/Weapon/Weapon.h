// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class APJPlayer;
class UWeaponData;

UCLASS()
class PLATFORMERJAM_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetData(UWeaponData* NewData);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE UWeaponData* GetData() const { return Data; }

	UFUNCTION(BlueprintCallable)
	void SetClipAmmo(int NewClip);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int GetClipAmmo() const { return ClipAmmo; }

	UFUNCTION(BlueprintCallable)
	virtual void Fire(const bool bHeld);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual bool CanFire(const bool bHeld);

	UFUNCTION(BlueprintCallable)
	virtual void Equip();

	UFUNCTION(BlueprintCallable)
	virtual void Unequip();

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static AWeapon* SpawnWeapon(UWeaponData* Data, APJPlayer* Player, UObject* WorldContextObject, int SpawnClip = -1);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWeaponData* Data = nullptr;

	UPROPERTY(BlueprintReadWrite)
	APJPlayer* Player = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ClipAmmo = -1;

	UPROPERTY(BlueprintReadOnly)
	float FireCooldown = 0;
};
