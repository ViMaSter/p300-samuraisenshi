// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PC_Ingame.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISENSHI_API APC_Ingame : public APlayerController
{
	GENERATED_UCLASS_BODY()

	AGameMode_General* GameModeReference;

	UENUM()
	enum PlayerCharacterBossPhase
	{
		PlayerCharacterBossPhase_Ready,
		PlayerCharacterBossPhase_Walking
	};

	TEnumAsByte<PlayerCharacterBossPhase> BossPhase;
	FVector DestinationPosition;

	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void SetCinematicMode(bool bInCinematicMode, bool bAffectsMovement, bool bAffectsTurning, FVector EndPosition);

	UFUNCTION(BlueprintCallable, Category = World)
	FString GetLevelName();
};
