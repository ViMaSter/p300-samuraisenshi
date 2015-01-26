// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "GameInstance_General.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISENSHI_API UGameInstance_General : public UGameInstance
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Session)
	int32 Playthrough;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Session)
	int32 Area;
};
