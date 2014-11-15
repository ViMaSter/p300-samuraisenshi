// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "Enemy_General.h"

AEnemy_General::AEnemy_General(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Setup attributes
	CharacterAttributes = PCIP.CreateDefaultSubobject<UComponent_CharacterAttributes>(this, TEXT("Character Attributes"));
	RootComponent = CharacterAttributes;
}

