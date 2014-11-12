// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GeneralCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISENSHI_API AGeneralCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Events")
		void doTakeDamage(int32 damage);
	UFUNCTION(BlueprintImplementableEvent, Category = "GeneralCharacter")
		virtual void onTakeDamage(int32 damage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeneralCharacter)
		int32 health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeneralCharacter)
		int32 damageDealing;
	
};
