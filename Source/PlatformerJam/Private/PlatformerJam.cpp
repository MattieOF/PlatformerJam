// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformerJam.h"

#include "PJLog.h"
#include "Modules/ModuleManager.h"

#if WITH_EDITOR
	#include "MessageLogModule.h"
#endif

DEFINE_LOG_CATEGORY(LogPJ);

IMPLEMENT_PRIMARY_GAME_MODULE( FPlatformerJamModule, PlatformerJam, "PlatformerJam" );

#define LOCTEXT_NAMESPACE "PlatformerJam"

void FPlatformerJamModule::StartupModule()
{
#if WITH_EDITOR
	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	FMessageLogInitializationOptions InitOptions;
	InitOptions.bShowPages = true;
	InitOptions.bAllowClear = true;
	InitOptions.bShowFilters = true;
	MessageLogModule.RegisterLogListing("PlatformerJam", NSLOCTEXT("PlatformerJam", "PlatformerJamLogLabel", "Platformer Jam"), InitOptions);
#endif
	
	// UE_LOG(LogPJ, Log, TEXT("Started main Platformer Jam module!"));
	PJ_LOG("Started main Platformer Jam module!");
}

void FPlatformerJamModule::ShutdownModule()
{
#if WITH_EDITOR
	if (FModuleManager::Get().IsModuleLoaded("MessageLog"))
	{
		// Unregister message log
		FMessageLogModule& MessageLogModule = FModuleManager::GetModuleChecked<FMessageLogModule>("MessageLog");
		MessageLogModule.UnregisterLogListing("PlatformerJam");
	}
#endif
	
	UE_LOG(LogPJ, Log, TEXT("Shutdown main Platformer Jam module!"));
}

#undef LOCTEXT_NAMESPACE
