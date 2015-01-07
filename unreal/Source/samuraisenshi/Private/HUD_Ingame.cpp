// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "HUD_Ingame.h"


AHUD_Ingame::AHUD_Ingame(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	CurrentInterfacePhase = InterfacePhase_Intro;
}


void AHUD_Ingame::UpdateInterfacePhase(EInterfacePhase newInterfacePhase)
{
	OnUpdateInterfacePhase(newInterfacePhase);

	EInterfacePhase oldInterfacePhase = CurrentInterfacePhase;
	CurrentInterfacePhase = newInterfacePhase;
}