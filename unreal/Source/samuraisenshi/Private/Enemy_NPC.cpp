// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "Enemy_NPC.h"

AEnemy_NPC::AEnemy_NPC(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Setup attributes
	CharacterAttributes = PCIP.CreateDefaultSubobject<UComponent_CharacterAttributes>(this, TEXT("Character Attributes"));
	RootComponent = CharacterAttributes;
}

