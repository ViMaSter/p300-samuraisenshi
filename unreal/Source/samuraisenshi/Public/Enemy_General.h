// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Component_CharacterAttributes.h"
#include "Enemy_General.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISENSHI_API AEnemy_General : public APawn
{
	GENERATED_UCLASS_BODY()

	/** General attributes every character in our game shares */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TSubobjectPtr<class UComponent_CharacterAttributes> CharacterAttributes;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser);
};
