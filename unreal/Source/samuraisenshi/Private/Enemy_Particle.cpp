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

	FlameAudio = PCIP.CreateDefaultSubobject<UAudioComponent>(this, TEXT("FlameAudio"));
	FlameAudio->AttachTo(Trail);

	DeathAudio = PCIP.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->AttachTo(Trail);

	DeathParticle = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("DeathParticle"));
	DeathParticle->AttachTo(RootComponent);
	DeathParticle->bVisible = false;

	DeadAfterSeconds = 0.0f;
	KeepDeathParticleForSeconds = 0.0f;
}


float AEnemy_Particle::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float previousSuper = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CharacterAttributes->CurrentRegularHealth <= 0)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorldTimerManager().SetTimer(this, &AEnemy_Particle::Kill, DeadAfterSeconds, true);
	}

	return previousSuper;
}

void AEnemy_Particle::Kill() {
	GetWorldTimerManager().ClearTimer(this, &AEnemy_Particle::Kill);

	Sphere->DestroyComponent();
	Trail->DestroyComponent();

	if (DeathAudio != NULL)
		DeathAudio->Play();

	DeathParticle->bVisible = true;
	IsDead = true;

	GetWorldTimerManager().SetTimer(this, &AEnemy_Particle::Die, KeepDeathParticleForSeconds, true);
}

void AEnemy_Particle::Die() {
	GetWorldTimerManager().ClearTimer(this, &AEnemy_Particle::Die);
	GetWorld()->DestroyActor(this);
}