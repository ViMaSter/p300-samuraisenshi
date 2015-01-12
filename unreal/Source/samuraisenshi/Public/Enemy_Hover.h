// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy_General.h"
#include "GameMode_General.h"
#include "Enemy_Hover.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISENSHI_API AEnemy_Hover : public AEnemy_General
{
	GENERATED_UCLASS_BODY()

	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	virtual void BeginBossFight();
	virtual void EndBossFight();

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
};
