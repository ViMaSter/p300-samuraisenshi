// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPC_Enemy.h"
#include "CharacterAttributesComponent.h"
#include "ParticleEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AParticleEnemy : public ANPC_Enemy
{
	GENERATED_UCLASS_BODY()

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Misc)
	TSubobjectPtr<class UStaticMeshComponent> Sphere;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Misc)
	TSubobjectPtr<class UParticleSystemComponent> Trail;


};
