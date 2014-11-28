// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "ActorTrigger_Boss.h"
#include "GameMode_General.generated.h"

enum BossPhase {
	EnteredTrigger,
	WalkingToPosition,
	WaitingForBossAnimation,
	InBattle,
	Defeated,
	Exiting
};

UCLASS(minimalapi)
class AGameMode_General : public AGameMode
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Session)
	uint32 Playthrough;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Session)
	uint32 Area;

	UPROPERTY(BlueprintReadOnly, Category = Session)
	AActorTrigger_Boss* BossTrigger;

	UPROPERTY(BlueprintReadOnly, Category = Session)
	uint32 BossPhase = 0;

	UPROPERTY()
	bool AllPlayerMovementDone;

	UFUNCTION(BlueprintCallable, Category = Session)
	void ToggleBoss(AActorTrigger_Boss* triggerZone);

	UFUNCTION()
	virtual void Tick(float deltaTime);
};



