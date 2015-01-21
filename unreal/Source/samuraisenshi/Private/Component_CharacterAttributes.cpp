// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "GameMode_General.h"
#include "Component_CharacterAttributes.h"


UComponent_CharacterAttributes::UComponent_CharacterAttributes(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bWantsInitializeComponent = true;
}

int32 UComponent_CharacterAttributes::get_SpawningRegularHealth()
{
	return SpawningRegularHealth;
};

int32 UComponent_CharacterAttributes::get_MaxRegularHealth()
{
	return SpawningRegularHealth;
};

int32 UComponent_CharacterAttributes::get_CurrentRegularHealth()
{
	return CurrentRegularHealth;
};

int32 UComponent_CharacterAttributes::set_RegularHealth(int32 NewRegularHealth, bool relative = false)
{
	if (relative)
	{
		CurrentRegularHealth += NewRegularHealth;
		CurrentRegularHealth = CurrentRegularHealth > MaxRegularHealth ? MaxRegularHealth : CurrentRegularHealth;
	}
	else
	{
		CurrentRegularHealth = NewRegularHealth > MaxRegularHealth ? MaxRegularHealth : NewRegularHealth;
	}

	return CurrentRegularHealth;
};

int32 UComponent_CharacterAttributes::get_SpawningRegularDamage()
{
	return SpawningRegularDamage;
};

int32 UComponent_CharacterAttributes::get_MaxRegularDamage()
{
	return MaxRegularDamage;
};

int32 UComponent_CharacterAttributes::get_CurrentRegularDamage()
{
	AGameMode_General* castedGameMode = Cast<AGameMode_General>(GetWorld()->GetAuthGameMode());
	int32 calculatedDamage = SpawningRegularDamage + (castedGameMode->Playthrough * AddPerPlaythroughDamage);
	
	return calculatedDamage > get_MaxRegularDamage() ? get_MaxRegularDamage() : calculatedDamage;
};

int32 UComponent_CharacterAttributes::set_RegularDamage(int NewRegularDamage, bool relative = false)
{
	if (relative)
	{
		CurrentRegularDamage += NewRegularDamage;
		CurrentRegularDamage = CurrentRegularDamage > MaxRegularDamage ? MaxRegularDamage : CurrentRegularDamage;
	}
	else
	{
		CurrentRegularDamage = NewRegularDamage > MaxRegularDamage ? MaxRegularDamage : NewRegularDamage;
	}

	return CurrentRegularDamage;
};


void UComponent_CharacterAttributes::InitializeComponent()
{
	Super::InitializeComponent();

	CurrentRegularDamage = SpawningRegularDamage;
	CurrentRegularHealth = SpawningRegularHealth;
}



AActor* UComponent_CharacterAttributes::get_LastHitBy(AActor* NewLastHitBy)
{
	return NewLastHitBy;
}

void UComponent_CharacterAttributes::set_LastHitBy(AActor* NewLastHitBy)
{
	LastHitBy = NewLastHitBy;
}