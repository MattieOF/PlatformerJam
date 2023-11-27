// copyright lololol

#include "AssetFactories.h"

#include "Enemy/EnemyData.h"
#include "Weapon/WeaponData.h"

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
	EnemyData->Name = FText::FromString(Name.ToString());
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
	WeaponData->Name = FText::FromString(Name.ToString());
	return WeaponData;
}
