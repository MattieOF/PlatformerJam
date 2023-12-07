#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "Enemy/EnemyData.h"
#include "Weapon/WeaponData.h"
#include "Weapon/Projectile/ProjectileData.h"

#define LOCTEXT_NAMESPACE "FPlatformerJamEditorModule"

extern EAssetTypeCategories::Type PJAssetCategory;

class FEnemyDataAssetActions final : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override { return LOCTEXT("EnemyData", "Enemy Data"); }
	virtual uint32 GetCategories() override { return PJAssetCategory; }
	virtual FColor GetTypeColor() const override { return FColor::Red; }
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override { return LOCTEXT("EnemyDataDesc", "Asset containing data for an enemy type."); }
	virtual UClass* GetSupportedClass() const override { return UEnemyData::StaticClass(); }
};

class FWeaponDataAssetActions final : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override { return LOCTEXT("WeaponData", "Weapon Data"); }
	virtual uint32 GetCategories() override { return PJAssetCategory; }
	virtual FColor GetTypeColor() const override { return FColor::Cyan; }
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override { return LOCTEXT("WeaponDataDesc", "Asset containing data for a weapon type."); }
	virtual UClass* GetSupportedClass() const override { return UWeaponData::StaticClass(); }
};

class FProjectileDataAssetActions final : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override { return LOCTEXT("ProjectileData", "Projectile Data"); }
	virtual uint32 GetCategories() override { return PJAssetCategory; }
	virtual FColor GetTypeColor() const override { return FColor::Yellow; }
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override { return LOCTEXT("ProjectileDataDesc", "Asset containing data for a projectile type."); }
	virtual UClass* GetSupportedClass() const override { return UProjectileData::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
