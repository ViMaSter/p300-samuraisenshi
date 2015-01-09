// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "Damage_Heal_General.h"
#include "Enemy_Particle.h"


AEnemy_Particle::AEnemy_Particle(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FObjectFinder <UStaticMesh> SphereMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));
	
	Sphere = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Sphere"));
	Sphere->SetStaticMesh(SphereMesh.Object);
	Sphere->AttachTo(RootComponent);

	Trail = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("Trail"));
	Trail->AttachTo(RootComponent);

	DeathParticle = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("DeathParticle"));
	DeathParticle->AttachTo(RootComponent);
	DeathParticle->bVisible = false;

	DeadAfterSeconds = 0.0f;
}


float AEnemy_Particle::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float previousSuper = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CharacterAttributes->set_RegularHealth(0, true) <= 0)
	{
		Kill();
	}

	return previousSuper;
}

void AEnemy_Particle::Kill() {
	Sphere->DestroyComponent();
	Trail->DestroyComponent();

	DeathParticle->bVisible = true;
	IsDead = true;

	GetWorldTimerManager().SetTimer(this, &AEnemy_Particle::Die, DeadAfterSeconds, true);
}

void AEnemy_Particle::Die() {
	GetWorld()->DestroyActor(this);
}