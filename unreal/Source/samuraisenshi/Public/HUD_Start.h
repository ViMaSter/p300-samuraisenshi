// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "HUD_Start.generated.h"

UENUM(BlueprintType)
enum HUD_Menu{
	HUD_Menu_StartUp,
	HUD_Menu_Start,
	HUD_Menu_Controls,
	HUD_Menu_Credits,
	HUD_Menu_Pause,
	HUD_Menu_Level_Finished,
	HUD_Menu_Game_Over
};

/**
 * 
 */
UCLASS()
class SAMURAISENSHI_API AHUD_Start : public AHUD
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HUDState)
	TEnumAsByte<HUD_Menu> MenuShown = HUD_Menu::HUD_Menu_StartUp;
};
