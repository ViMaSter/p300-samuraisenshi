// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
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


}


float AEnemy_Particle::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CharacterAttributes->set_RegularDamage(-floor(DamageAmount), true) <= 0)
	{
		GetWorld()->DestroyActor(this);
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}