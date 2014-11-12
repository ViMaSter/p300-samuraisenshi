// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "GeneralCharacter.h"


AGeneralCharacter::AGeneralCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AGeneralCharacter::doTakeDamage(int32 damage)
{
	health -= damage;
	if (health < 0)
		Destroy(false, true);
}

