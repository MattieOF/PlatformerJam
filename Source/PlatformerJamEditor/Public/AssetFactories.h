﻿// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AssetFactories.generated.h"

UCLASS()
class UEnemyDataFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UEnemyDataFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class UWeaponDataFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UWeaponDataFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
