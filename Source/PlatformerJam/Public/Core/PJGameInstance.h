// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PJGameInstance.generated.h"

/**
 * Base Game Instance class for PJ.
 */
UCLASS()
class PLATFORMERJAM_API UPJGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void Log(FString Message);
	
	UFUNCTION(BlueprintCallable)
	static void LogText(FText Message);

	UFUNCTION(BlueprintCallable)
	static void LogError(FString Message);
	
	UFUNCTION(BlueprintCallable)
	static void LogTextError(FText Message);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static FORCEINLINE UPJGameInstance* GetPJGameInstance(UObject* WorldContextObject)
	{
		return Cast<UPJGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	}
};
