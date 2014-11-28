// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "samuraisenshi.h"
#include "GameMode_General.h"
#include "Character_General.h"
#include "DrawDebugHelpers.h"

AGameMode_General::AGameMode_General(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Playthrough = 0;
	Area = 0;
	BossPhase = 0;
	BossTrigger = NULL;
	AllPlayerMovementDone = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Character/Player/C_Ingame_Default"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


void AGameMode_General::ToggleBoss(AActorTrigger_Boss* triggerZone) {
	if (BossTrigger != NULL)							// already triggered a boss
		return;
	if (triggerZone == NULL && BossTrigger == NULL)		// useless call
		return;

	if (BossPhase == EnteredTrigger) {								// everything seems fine
		BossTrigger = triggerZone;
		for (TActorIterator<APlayerController> PC_Iterator(GetWorld()); PC_Iterator; ++PC_Iterator) {
			APlayerController* currentPC = *PC_Iterator;

			currentPC->SetCinematicMode(true, true, false);
		}
		BossPhase = BossPhase::WalkingToPosition;
	}
	else {
		return; // weird error
	}
}

void AGameMode_General::Tick(float delaTime) {
	switch (BossPhase) {
		case BossPhase::EnteredTrigger:
			break;
		case 1:
			AllPlayerMovementDone = true;
			for (TActorIterator<APlayerController> PC_Iterator(GetWorld()); PC_Iterator; ++PC_Iterator) {
				APlayerController* currentPC = *PC_Iterator;

				if (currentPC->GetCharacter()->GetActorLocation().Y + 20 < BossTrigger->GetActorLocation().Y) {
					currentPC->GetCharacter()->AddMovementInput(FVector(0, 1, 0));
					AllPlayerMovementDone = false;
				}
				
				if (currentPC->GetCharacter()->GetActorLocation().Y - 20 > BossTrigger->GetActorLocation().Y) {
					currentPC->GetCharacter()->AddMovementInput(FVector(0, -1, 0));
					AllPlayerMovementDone = false;
				}
			}

			if (AllPlayerMovementDone) {
				BossPhase = WaitingForBossAnimation;
			}
			break;
		case BossPhase::WaitingForBossAnimation:

			break;
		case BossPhase::InBattle:
			break;
		case BossPhase::Defeated:
			break;
		case BossPhase::Exiting:
			break;
	}
}