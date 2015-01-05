// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy_General.h"
#include "Enemy_Particle.generated.h"

/**
 * 
 */
UCLASS()
class AEnemy_Particle : public AEnemy_General
{
	GENERATED_UCLASS_BODY()

	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Misc)
	TSubobjectPtr<class UStaticMeshComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Misc)
	TSubobjectPtr<class UParticleSystemComponent> Trail;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Misc)
	TSubobjectPtr<class UParticleSystemComponent> DeathParticle;
};
