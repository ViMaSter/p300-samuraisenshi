// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enemy_General.h"
#include "ActorSpawner_General.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISENSHI_API AActorSpawner_General : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	TSubclassOf<class AEnemy_General> enemyToSpawn;

	void DoSpawn();
};
