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
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	FORCEINLINE UPJGameInstance* GetPJGameInstance(UObject* WorldContextObject)
	{
		return Cast<UPJGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	}
};
