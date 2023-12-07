// copyright lololol

#include "Enemy/Gibs.h"

AGibs::AGibs()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGibs::BeginPlay()
{
	Super::BeginPlay();
	GetComponents<USceneComponent>(Gibs);
}

void AGibs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;

	const float Mapped = FMath::GetMappedRangeValueUnclamped(FadeOutRange, FVector2f(0, 1), ElapsedTime);
	if (Mapped >= 1.2)
	{
		Destroy();
	}
	else if (Mapped > 0)
	{
		for (const auto Component : Gibs)
			Component->SetRelativeScale3D(FVector(FMath::Max(1 - Mapped, 0)));
	}
}
