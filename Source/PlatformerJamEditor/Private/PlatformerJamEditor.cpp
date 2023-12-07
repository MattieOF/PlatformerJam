#include "PlatformerJamEditor.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "PJEditorLog.h"

IMPLEMENT_MODULE(FPlatformerJamEditorModule, PlatformerJamEditor)
DEFINE_LOG_CATEGORY(LogPJEditor)

#define LOCTEXT_NAMESPACE "FPlatformerJamEditorModule"

EAssetTypeCategories::Type PJAssetCategory;

void FPlatformerJamEditorModule::StartupModule()
{
	UE_LOG(LogPJEditor, Warning, TEXT("Initialise PJEditor module"));
	
	IAssetTools &AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    PJAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("PJCategory")),LOCTEXT("PJCategory", "Platformer Jam"));
    EnemyDataAssetActions = MakeShared<FEnemyDataAssetActions>();
	AssetTools.RegisterAssetTypeActions(EnemyDataAssetActions.ToSharedRef());
	WeaponDataAssetActions = MakeShared<FWeaponDataAssetActions>();
	AssetTools.RegisterAssetTypeActions(WeaponDataAssetActions.ToSharedRef());
	ProjectileDataAssetActions = MakeShared<FProjectileDataAssetActions>();
	AssetTools.RegisterAssetTypeActions(ProjectileDataAssetActions.ToSharedRef());
}

void FPlatformerJamEditorModule::ShutdownModule()
{ }

#undef LOCTEXT_NAMESPACE
