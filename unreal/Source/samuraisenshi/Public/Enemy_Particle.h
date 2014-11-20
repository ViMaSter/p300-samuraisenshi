// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy_NPC.h"
#include "Enemy_Particle.generated.h"

/**
 * 
 */
UCLASS()
class AEnemy_Particle : public AEnemy_NPC
{
	GENERATED_UCLASS_BODY()

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Misc)
	TSubobjectPtr<class UStaticMeshComponent> Sphere;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Misc)
	TSubobjectPtr<class UParticleSystemComponent> Trail;


};