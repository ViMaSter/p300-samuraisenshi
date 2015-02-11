// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "HUD_Start.h"
#include "HUD_Ingame.generated.h"

UENUM()
enum EInterfacePhase
{
	InterfacePhase_Intro,
	InterfacePhase_Ingame,
	InterfacePhase_Dead
};

UCLASS()
class SAMURAISENSHI_API AHUD_Ingame : public AHUD
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadOnly, Category = Interface)
	TEnumAsByte<EInterfacePhase> CurrentInterfacePhase;

	UFUNCTION(BlueprintCallable, Category = Interface)
	void UpdateInterfacePhase(EInterfacePhase newInterfacePhase);

	UFUNCTION(BlueprintImplementableEvent, Category = Interface)
	virtual void OnUpdateInterfacePhase(EInterfacePhase newInterfacePhase);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HUDState)
	TEnumAsByte<HUD_Menu> MenuShown = HUD_Menu::HUD_Menu_NONE;
};
