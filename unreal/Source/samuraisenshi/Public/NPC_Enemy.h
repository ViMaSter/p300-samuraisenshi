// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Component_CharacterAttributes.h"
#include "NPC_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISENSHI_API ANPC_Enemy : public APawn
{
	GENERATED_UCLASS_BODY()

	/** General attributes every character in our game shares */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TSubobjectPtr<class UComponent_CharacterAttributes> CharacterAttributes;

};
