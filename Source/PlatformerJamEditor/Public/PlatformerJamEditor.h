#pragma once

#include "CoreMinimal.h"
#include "AssetActions.h"
#include "AssetTypeCategories.h"
#include "Modules/ModuleManager.h"

extern EAssetTypeCategories::Type PJAssetCategory;

class FPlatformerJamEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
	
	TSharedPtr<FEnemyDataAssetActions>      EnemyDataAssetActions;
	TSharedPtr<FWeaponDataAssetActions>     WeaponDataAssetActions;
	TSharedPtr<FProjectileDataAssetActions> ProjectileDataAssetActions;
};
