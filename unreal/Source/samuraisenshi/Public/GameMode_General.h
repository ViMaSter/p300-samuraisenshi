// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "ActorTrigger_Boss.h"
#include "GameMode_General.generated.h"

UCLASS(minimalapi)
class AGameMode_General : public AGameMode
{
	GENERATED_UCLASS_BODY()

	UENUM()
	enum BossPhase {
		BossPhase_Idle,
		BossPhase_EnteredTrigger,
		BossPhase_WaitingForPlayerAndCamera,
		BossPhase_SpawnBoss,
		BossPhase_WaitingForBossAnimation,
		BossPhase_InBattle,
		BossPhase_Defeated,
		BossPhase_Exiting
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Session)
	int32 Playthrough;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Session)
	int32 Area;

	UPROPERTY(BlueprintReadOnly, Category = Session)
	TEnumAsByte<BossPhase> CurrentBossPhase;

	UPROPERTY(BlueprintReadOnly, Category = Session)
	AActorTrigger_Boss* BossTrigger;

	UPROPERTY(BlueprintReadOnly, Category = Logic)
	FVector PlayerTargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Logic)
	float BossMovementAccuracy;

	bool AllPlayerMovementDone;

	UFUNCTION(BlueprintCallable, Category = Session)
	void ToggleBoss(AActorTrigger_Boss* triggerZone);

	// Use thins with "BossPhase_InBattle", when the enemy-animation is done
	void UpdateBossPhase(BossPhase newBossPhase);

	UFUNCTION()
	virtual void Tick(float deltaTime);
};



