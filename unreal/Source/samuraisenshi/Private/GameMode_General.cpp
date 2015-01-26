// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "samuraisenshi.h"
#include "GameMode_General.h"
#include "Character_General.h"
#include "PC_Ingame.h"
#include "DrawDebugHelpers.h"

AGameMode_General::AGameMode_General(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP)
{
	CurrentBossPhase = BossPhase_Idle;

	BossTrigger = NULL;
	PlayerTargetLocation = FVector::ZeroVector;
	BossMovementAccuracy = 20.0f;

	AllPlayerMovementDone = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Character/Player/C_Ingame_Default"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AGameMode_General::ToggleBoss(AActorTrigger_Boss* triggerZone) {
	if (BossTrigger != NULL)								// already triggered a boss
		return;
	if (triggerZone == NULL && BossTrigger == NULL)			// useless call
		return;

	if (CurrentBossPhase != BossPhase_Idle)					// something is bogus
		return;

	BossTrigger = triggerZone;

	UpdateBossPhase(BossPhase_EnteredTrigger);

	PlayerTargetLocation = FVector(triggerZone->AbsoluteEndCameraPosition);

	UpdateBossPhase(BossPhase_WaitingForPlayerAndCamera);
}

void AGameMode_General::UpdateBossPhase(BossPhase newBossPhase)
{
	BossPhase oldBossPhase = CurrentBossPhase;
	CurrentBossPhase = newBossPhase;

	switch (newBossPhase)
	{
	case BossPhase_WaitingForPlayerAndCamera:
		// prepare each player
		for (TActorIterator<APC_Ingame> PC_Iterator(GetWorld()); PC_Iterator; ++PC_Iterator) {
			APC_Ingame* currentPC = *PC_Iterator;

			currentPC->SetCinematicMode(true, true, false, PlayerTargetLocation);
			currentPC->BossPhase = APC_Ingame::PlayerCharacterBossPhase_Walking;
		}
		break;

	case BossPhase_WaitingForBossAnimation:
		BossTrigger->CurrentPhase = AActorTrigger_Boss::BossTriggerPhase_Spawning;
		break;

	case BossPhase_InBattle:
		for (TActorIterator<APC_Ingame> PC_Iterator(GetWorld()); PC_Iterator; ++PC_Iterator) {
			APC_Ingame* currentPC = *PC_Iterator;
			currentPC->SetCinematicMode(false, false, false, PlayerTargetLocation);
		}
		break;

	case BossPhase_Defeated:
		for (TActorIterator<APC_Ingame> PC_Iterator(GetWorld()); PC_Iterator; ++PC_Iterator) {
			APC_Ingame* currentPC = *PC_Iterator;

			currentPC->SetCinematicMode(true, true, false, PlayerTargetLocation);
		}
		break;

	case BossPhase_Exiting:
		for (TActorIterator<APC_Ingame> PC_Iterator(GetWorld()); PC_Iterator; ++PC_Iterator) {
			APC_Ingame* currentPC = *PC_Iterator;
			currentPC->SetCinematicMode(false, false, false, PlayerTargetLocation);
		}
		BossTrigger->CurrentPhase = AActorTrigger_Boss::BossTriggerPhase_FightOver;
		UpdateBossPhase(BossPhase_Idle);
		break;
	}
}

void AGameMode_General::Tick(float delaTime) {
	switch (CurrentBossPhase) {
	case BossPhase_WaitingForPlayerAndCamera:
		AllPlayerMovementDone = true;
		for (TActorIterator<APC_Ingame> PC_Iterator(GetWorld()); PC_Iterator; ++PC_Iterator) {
			APC_Ingame* currentPC = *PC_Iterator;

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Left: %f"), (currentPC->GetCharacter()->GetActorLocation().Y - PlayerTargetLocation.Y)));

			if (currentPC->GetCharacter()->GetActorLocation().Y + BossMovementAccuracy < PlayerTargetLocation.Y || currentPC->GetCharacter()->GetActorLocation().Y - BossMovementAccuracy > PlayerTargetLocation.Y) {
				currentPC->BossPhase = APC_Ingame::PlayerCharacterBossPhase_Walking;
				AllPlayerMovementDone = false;
			}
			else {
				currentPC->BossPhase = APC_Ingame::PlayerCharacterBossPhase_Ready;
			}
		}

		if (AllPlayerMovementDone && BossTrigger->TransitionCurrentAt > 1.0f) {
			BossTrigger->CurrentPhase = AActorTrigger_Boss::BossTriggerPhase_Fighting;
			UpdateBossPhase(BossPhase_WaitingForBossAnimation);
		}
		break;
	}
}