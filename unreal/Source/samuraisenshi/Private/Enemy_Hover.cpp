// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "Enemy_Hover.h"


AEnemy_Hover::AEnemy_Hover(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


float AEnemy_Hover::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float newLife = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (newLife <= 0)
	{
		Cast<AGameMode_General>(GetWorld()->GetAuthGameMode())->UpdateBossPhase(AGameMode_General::BossPhase_Defeated);
		GetWorldTimerManager().SetTimer(this, &AEnemy_Hover::EndBossFight, 2.0f, true);
	}
	return newLife;
}

void AEnemy_Hover::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(this, &AEnemy_Hover::BeginBossFight, 2.0f, true);
}

void AEnemy_Hover::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}



void AEnemy_Hover::BeginBossFight()
{
	GetWorldTimerManager().ClearTimer(this, &AEnemy_Hover::BeginBossFight);

	Cast<AGameMode_General>(GetWorld()->GetAuthGameMode())->UpdateBossPhase(AGameMode_General::BossPhase_InBattle);
}

void AEnemy_Hover::EndBossFight()
{
	GetWorldTimerManager().ClearTimer(this, &AEnemy_Hover::EndBossFight);

	Cast<AGameMode_General>(GetWorld()->GetAuthGameMode())->UpdateBossPhase(AGameMode_General::BossPhase_Exiting);

	GetWorld()->DestroyActor(this);
}
