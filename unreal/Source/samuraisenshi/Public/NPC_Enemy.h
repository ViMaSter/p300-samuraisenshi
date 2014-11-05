// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "NPC_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISENSHI_API ANPC_Enemy : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		int32 health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		int32 damageDealing;
};
