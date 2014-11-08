// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GeneralCharacter.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class SAMURAISENSHI_API AGeneralCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Character)
	int32 SpawningHealth;

	UPROPERTY(EditAnywhere, Category = Character)
	int32 MaxHealth;

	UPROPERTY(EditAnywhere, Category = Character)
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, Category = Character)
	int32 SpawningRegularDamage;

	UPROPERTY(EditAnywhere, Category = Character)
	int32 MaxRegularDamage;

	UPROPERTY(EditAnywhere, Category = Character)
	int32 CurrentDamageDealing;

	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_SpawningHealth();

	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_MaxHealth();

	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_CurrentHealth();

	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_SpawningRegularDamage();

	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_MaxRegularDamage();

	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_CurrentDamageDealing();
	
	
};
