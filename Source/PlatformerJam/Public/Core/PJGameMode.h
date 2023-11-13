// copyright lololol

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PJGameMode.generated.h"

/**
 * Base game mode class for PJ.
 */
UCLASS()
class PLATFORMERJAM_API APJGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	FORCEINLINE APJGameMode* GetPJGameMode(UObject* WorldContextObject)
	{
		return Cast<APJGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	}
};
