// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "GeneralCharacter.h"


AGeneralCharacter::AGeneralCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

int32 AGeneralCharacter::get_SpawningHealth()
{
	return SpawningHealth;
};

int32 AGeneralCharacter::get_MaxHealth()
{
	return SpawningHealth;
};

int32 AGeneralCharacter::get_CurrentHealth()
{
	return CurrentHealth;
};

int32 AGeneralCharacter::get_SpawningRegularDamage()
{
	return SpawningRegularDamage;
};

int32 AGeneralCharacter::get_MaxRegularDamage()
{
	return MaxRegularDamage;
};

int32 AGeneralCharacter::get_CurrentDamageDealing()
{
	return CurrentDamageDealing;
};


