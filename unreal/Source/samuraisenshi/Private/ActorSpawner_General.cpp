// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "Engine.h"
#include "ActorSpawner_General.h"


AActorSpawner_General::AActorSpawner_General(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AActorSpawner_General::DoSpawn() {
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;
	SpawnParams.bNoCollisionFail = true;

	GetWorld()->SpawnActor<AEnemy_General>(enemyToSpawn, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
}
