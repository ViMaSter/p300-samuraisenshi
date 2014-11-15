// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"

#include "Character_General.h"
#include "ActorSpawner_General.h"

#include "ActorTrigger_General.generated.h"

USTRUCT()
struct FEnemySpawn {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	float SpawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	AActorSpawner_General* SpawnToTrigger;
};

/**
 * 
 */
UCLASS(DefaultToInstanced, abstract)
class SAMURAISENSHI_API AActorTrigger_General : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	TArray<FEnemySpawn> EnemySpawns;

	bool triggered = false;
	int32 currentlyAtIndex = 0;

	void QueueSpawn();
	void RunSpawn();
	void SpawnNext();

	UShapeComponent* CastedTrigger;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void ReceiveActorBeginOverlap(AActor* OtherActor);
};
