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

	UFUNCTION(BlueprintCallable, Category = Character)
	void Kill();

	void Die();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Misc)
	TSubobjectPtr<class UStaticMeshComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Misc)
	TSubobjectPtr<class UParticleSystemComponent> Trail;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Audio)
	TSubobjectPtr<class UAudioComponent> FlameAudio;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Audio)
	TSubobjectPtr<class UAudioComponent> DeathOnCollisionAudio;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Audio)
	TSubobjectPtr<class UAudioComponent> DeathOnHitAudio;

	TSubobjectPtr<class UAudioComponent>* DeathSoundToUse;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Death)
	bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Death)
	float DeadAfterSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Death)
	float KeepDeathParticleForSeconds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Death)
	TSubobjectPtr<class UParticleSystemComponent> DeathParticle;
};
