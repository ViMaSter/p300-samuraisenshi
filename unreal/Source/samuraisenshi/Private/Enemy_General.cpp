// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "Damage_Heal_General.h"
#include "Enemy_General.h"

AEnemy_General::AEnemy_General(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Setup attributes
	CharacterAttributes = PCIP.CreateDefaultSubobject<UComponent_CharacterAttributes>(this, TEXT("Character Attributes"));
	RootComponent = CharacterAttributes;
}

float AEnemy_General::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CharacterAttributes->LastHitBy = DamageCauser;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%s got hit! (%f)"), *this->GetName(), DamageAmount));

	// enemy is dead
	if (CharacterAttributes->set_RegularDamage(-floor(DamageAmount), true) <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%s died! (%f)"), *this->GetName(), CharacterAttributes->get_CurrentRegularHealth()));
		CharacterAttributes->LastHitBy->TakeDamage(float(-CharacterAttributes->RegularRegeneration), FDamageEvent(UDamage_Heal_General::StaticClass()), GetWorld()->GetFirstPlayerController(), this);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%s got healed! (%f)"), *this->GetName(), float(-CharacterAttributes->RegularRegeneration)));
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
