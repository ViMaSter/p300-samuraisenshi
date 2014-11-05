// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "ParticleEnemy.h"


AParticleEnemy::AParticleEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Trail = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("Trail"));
	Trail->AttachTo(RootComponent);

	health = 5;
	damageDealing = 1;
}

void AParticleEnemy::doTakeDamage(int32 damage)
{
	health -= damage;
	if (health < 0)
		Destroy(false, true);
}