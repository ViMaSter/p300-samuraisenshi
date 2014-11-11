// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "samuraisenshi.h"
#include "GameMode_General.h"
#include "Character_General.h"

AGameMode_General::AGameMode_General(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Character/C_Ingame_Default"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
