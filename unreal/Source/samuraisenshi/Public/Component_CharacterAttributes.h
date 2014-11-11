// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Component_CharacterAttributes.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class SAMURAISENSHI_API UComponent_CharacterAttributes : public USceneComponent
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Character)
	int32 SpawningRegularHealth;

	UPROPERTY(EditAnywhere, Category = Character)
	int32 MaxRegularHealth;

	UPROPERTY()
	int32 CurrentRegularHealth;

	UPROPERTY(EditAnywhere, Category = Character)
	int32 SpawningRegularDamage;

	UPROPERTY(EditAnywhere, Category = Character)
	int32 MaxRegularDamage;

	UPROPERTY()
	int32 CurrentRegularDamage;



	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_SpawningRegularHealth();

	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_MaxRegularHealth();

	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_CurrentRegularHealth();


	UFUNCTION(BlueprintCallable, Category = Character)
	int32 set_RegularHealth(int32 NewRegularHealth, bool relative);



	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_SpawningRegularDamage();

	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_MaxRegularDamage();

	UFUNCTION(BlueprintCallable, Category = Character)
	int32 get_CurrentRegularDamage();


	UFUNCTION(BlueprintCallable, Category = Character)
	int32 set_RegularDamage(int32 NewRegularHealth, bool relative);



	virtual void InitializeComponent() override;
};
