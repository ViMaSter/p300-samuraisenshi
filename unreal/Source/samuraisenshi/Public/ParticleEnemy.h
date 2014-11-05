// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ParticleEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AParticleEnemy : public ACharacter
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	int32 health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	int32 damageDealing;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Misc)
	TSubobjectPtr<class UParticleSystemComponent> Trail;

public:

	UFUNCTION(BlueprintCallable, Category = "Events")
	void doTakeDamage(int32 damage);
};
