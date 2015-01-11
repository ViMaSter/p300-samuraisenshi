// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "GameMode_General.h"
#include "PC_Ingame.h"
#include "Engine.h"


APC_Ingame::APC_Ingame(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void APC_Ingame::BeginPlay()
{
	Super::BeginPlay();

	GameModeReference = Cast<AGameMode_General>(GetWorld()->GetAuthGameMode());
}

void APC_Ingame::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (BossPhase == PlayerCharacterBossPhase_Walking) {
		GetCharacter()->AddMovementInput(FVector(
			0.f,
			GetCharacter()->GetActorLocation().Y < DestinationPosition.Y ? 1.0f : -1.0f,
			0.f
		), 1, true);
	}
}

void APC_Ingame::SetCinematicMode(bool bInCinematicMode, bool bAffectsMovement, bool bAffectsTurning, FVector EndPosition)
{
	SetIgnoreMoveInput(bAffectsMovement);

	DestinationPosition = EndPosition;
}

FString APC_Ingame::GetLevelName() {
	return GetWorld()->GetMapName().Replace(*(GetWorld()->StreamingLevelsPrefix), TEXT(""), ESearchCase::IgnoreCase);
}