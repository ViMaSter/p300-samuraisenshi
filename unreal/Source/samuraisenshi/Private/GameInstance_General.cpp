// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "GameInstance_General.h"


UGameInstance_General::UGameInstance_General(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Playthrough = 0;
	Area = 0;
}


