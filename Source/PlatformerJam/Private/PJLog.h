#pragma once

#if WITH_EDITOR
	#include "MessageLogModule.h"
#endif

DECLARE_LOG_CATEGORY_EXTERN(LogPJ, Log, All);

#if WITH_EDITOR
	#define PJ_LOG(x) FMessageLog("PlatformerJam").Info(FText::FromString(x));
	#define PJ_LOG_ERROR(x) do { FMessageLog("PlatformerJam").Error(FText::FromString(x));\
	{ FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");\
	MessageLogModule.OpenMessageLog("PlatformerJam");} } while(false)
#else
	#define PJ_LOG(x) UE_LOG(LogPJ, Log, TEXT(x));
	#define PJ_LOG_ERROR(x) UE_LOG(LogPJ, Error, TEXT(x));
#endif
