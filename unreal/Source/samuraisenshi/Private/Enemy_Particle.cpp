// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "Damage_PlayerSlash.h"
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

	DeathOnCollisionAudio = PCIP.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathOnCollisionAudio"));
	DeathOnCollisionAudio->AttachTo(Trail);

	DeathOnHitAudio = PCIP.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathOnHitAudio"));
	DeathOnHitAudio->AttachTo(Trail);

	DeathParticle = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("DeathParticle"));
	DeathParticle->AttachTo(RootComponent);
	DeathParticle->bVisible = true;
	DeathParticle->bAutoActivate = false;

	HitParticle = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("HitParticle"));
	HitParticle->AttachTo(RootComponent);
	HitParticle->bVisible = true;
	HitParticle->bAutoActivate = false;

	DeadAfterSeconds = 0.0f;
	KeepDeathParticleForSeconds = 0.0f;
}


float AEnemy_Particle::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float previousSuper = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CharacterAttributes->CurrentRegularHealth <= 0)
	{
		DeathSoundToUse = DamageEvent.DamageTypeClass->IsChildOf(UDamage_PlayerSlash::StaticClass()) != NULL ? &DeathOnHitAudio : &DeathOnCollisionAudio;

		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorldTimerManager().SetTimer(this, &AEnemy_Particle::Kill, DeadAfterSeconds, true);
	}
	else {
		HitParticle->Activate(true);
	}

	return previousSuper;
}

void AEnemy_Particle::Kill() {
	GetWorldTimerManager().ClearTimer(this, &AEnemy_Particle::Kill);

	Sphere->DestroyComponent();
	Trail->DestroyComponent();

	if (*DeathSoundToUse != NULL)
		(*DeathSoundToUse)->Play();

	DeathParticle->Activate(true);
	IsDead = true;

	GetWorldTimerManager().SetTimer(this, &AEnemy_Particle::Die, KeepDeathParticleForSeconds, true);
}

void AEnemy_Particle::Die() {
	GetWorldTimerManager().ClearTimer(this, &AEnemy_Particle::Die);
	GetWorld()->DestroyActor(this);
}