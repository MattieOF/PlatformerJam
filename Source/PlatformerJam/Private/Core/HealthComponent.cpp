// copyright lololol

#include "Core/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.SetTickFunctionEnable(bAllowOverheal);
}

void UHealthComponent::SetAllowsOverheal(bool bNewValue, bool bClampHealth)
{
	bAllowOverheal = bNewValue;
	PrimaryComponentTick.SetTickFunctionEnable(bAllowOverheal);
	if (!bAllowOverheal && bClampHealth && CurrentHealth > MaxHealth)
		SetHealth(MaxHealth);
}

void UHealthComponent::SetAllowsNegative(bool bNewValue, bool bClampHealth)
{
	bAllowNegative = bNewValue;
	if (!bAllowNegative && bClampHealth && CurrentHealth < 0)
		SetHealth(0);
}

void UHealthComponent::SetHealth(float NewHealth)
{
	float OldHealth = CurrentHealth;
	
	if (!bAllowOverheal)
		NewHealth = FMath::Min(NewHealth, MaxHealth);
	if (!bAllowNegative)
		NewHealth = FMath::Max(NewHealth, 0);
	
	CurrentHealth = NewHealth;

	const float Difference = NewHealth - OldHealth;
	if (Difference > 0)
		OnHealed.Broadcast(NewHealth, Difference);
	else if (Difference < 0)
		OnHurt.Broadcast(NewHealth, FMath::Abs(Difference));
	
	OnHealthChanged.Broadcast(NewHealth);
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

void UHealthComponent::Damage(float Amount)
{
	SetHealth(CurrentHealth - Amount);
}

void UHealthComponent::Heal(float Amount)
{
	SetHealth(CurrentHealth + Amount);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentHealth > MaxHealth)
		CurrentHealth = FMath::Max(CurrentHealth -= OverhealDecayRate * DeltaTime, MaxHealth);
}
