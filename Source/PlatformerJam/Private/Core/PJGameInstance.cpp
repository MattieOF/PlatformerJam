// copyright lololol

#include "Core/PJGameInstance.h"

#include "PJLog.h"

void UPJGameInstance::Log(FString Message)
{
	PJ_LOG(Message);
}

void UPJGameInstance::LogText(FText Message)
{
	PJ_LOG(Message.ToString());
}

void UPJGameInstance::LogError(FString Message)
{
	PJ_LOG_ERROR(Message);
}

void UPJGameInstance::LogTextError(FText Message)
{
	PJ_LOG_ERROR(Message.ToString());
}
