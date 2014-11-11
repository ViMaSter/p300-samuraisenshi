// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "NPC_Enemy.h"

ANPC_Enemy::ANPC_Enemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Setup attributes
	CharacterAttributes = PCIP.CreateDefaultSubobject<UComponent_CharacterAttributes>(this, TEXT("Character Attributes"));
	RootComponent = CharacterAttributes;
}

