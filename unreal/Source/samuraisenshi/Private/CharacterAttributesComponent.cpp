// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "CharacterAttributesComponent.h"


UCharacterAttributesComponent::UCharacterAttributesComponent(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

int32 UCharacterAttributesComponent::get_SpawningRegularHealth()
{
	return SpawningRegularHealth;
};

int32 UCharacterAttributesComponent::get_MaxRegularHealth()
{
	return SpawningRegularHealth;
};

int32 UCharacterAttributesComponent::get_CurrentRegularHealth()
{
	return CurrentRegularHealth;
};

int32 UCharacterAttributesComponent::set_RegularHealth(int32 NewRegularHealth, bool relative = false)
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

int32 UCharacterAttributesComponent::get_SpawningRegularDamage()
{
	return SpawningRegularDamage;
};

int32 UCharacterAttributesComponent::get_MaxRegularDamage()
{
	return MaxRegularDamage;
};

int32 UCharacterAttributesComponent::get_CurrentRegularDamage()
{
	return CurrentRegularDamage;
};

int32 UCharacterAttributesComponent::set_RegularDamage(int NewRegularDamage, bool relative = false)
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


void UCharacterAttributesComponent::InitializeComponent()
{
	Super::InitializeComponent();

	CurrentRegularDamage = SpawningRegularDamage;
	CurrentRegularHealth = SpawningRegularHealth;
}