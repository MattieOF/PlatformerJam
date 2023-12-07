// copyright lololol

#include "AssetFactories.h"

#include "Enemy/EnemyData.h"
#include "Weapon/WeaponData.h"
#include "Weapon/Projectile/ProjectileData.h"

FString FactoryStatics::GetAssetNameWithoutPrefix(FString Name)
{
	TArray<FString> Sections;
	const TCHAR Sep = '_';
	Name.ParseIntoArray(Sections, &Sep);
	return Sections.Last();
}

UEnemyDataFactory::UEnemyDataFactory()
{
	SupportedClass = UEnemyData::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UEnemyDataFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	auto EnemyData = NewObject<UEnemyData>(InParent, Class, Name, Flags, Context);
	EnemyData->Name = FText::FromString(FactoryStatics::GetAssetNameWithoutPrefix(Name.ToString()));
	return EnemyData;
}

UWeaponDataFactory::UWeaponDataFactory()
{
	SupportedClass = UWeaponData::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UWeaponDataFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	auto WeaponData = NewObject<UWeaponData>(InParent, Class, Name, Flags, Context);
	WeaponData->Name = FText::FromString(FactoryStatics::GetAssetNameWithoutPrefix(Name.ToString()));
	return WeaponData;
}

UProjectileDataFactory::UProjectileDataFactory()
{
	SupportedClass = UProjectileData::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UProjectileDataFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	auto ProjectileData = NewObject<UProjectileData>(InParent, Class, Name, Flags, Context);
	ProjectileData->Name = FText::FromString(FactoryStatics::GetAssetNameWithoutPrefix(Name.ToString()));
	return ProjectileData;
}
