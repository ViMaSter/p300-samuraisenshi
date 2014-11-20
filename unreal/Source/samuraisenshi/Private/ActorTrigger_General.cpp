// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "Engine.h"
#include "ActorSpawner_General.h"
#include "ActorTrigger_General.h"


AActorTrigger_General::AActorTrigger_General(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void AActorTrigger_General::BeginPlay()
{
	Super::BeginPlay();

	CastedTrigger = Cast<UShapeComponent>(RootComponent);

	if (EnemySpawns.Num() > 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Spawner set!"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Spawner set!"));
	}

	if (CastedTrigger) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Valid Trigger!"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Invalid Trigger!"));
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Trigger: %s"), *this->GetName()));
}


void AActorTrigger_General::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AActorTrigger_General::ReceiveActorBeginOverlap(AActor* OtherActor) {
	if (Cast<ACharacter_General>(OtherActor)) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Collision: \"%s\""), *OtherActor->GetName()));
		QueueSpawn();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Weird collision: \"%s\""), *OtherActor->GetName()));
	}
}

void AActorTrigger_General::QueueSpawn() {
	if (!triggered) {
		triggered = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Trigger \"%s\" launched!"), *GetName()));

		if (currentlyAtIndex < EnemySpawns.Num()) {
			if (EnemySpawns[currentlyAtIndex].SpawnDelay > 0)
				GetWorldTimerManager().SetTimer(this, &AActorTrigger_General::RunSpawn, EnemySpawns[currentlyAtIndex].SpawnDelay, true);
			else
				RunSpawn();
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trigger \"%s\" already triggered!"), *GetName()));
	}
}

void AActorTrigger_General::RunSpawn() {
	GetWorldTimerManager().ClearTimer(this, &AActorTrigger_General::RunSpawn);
	Cast<AActorSpawner_General>(EnemySpawns[currentlyAtIndex].SpawnToTrigger)->DoSpawn();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Trigger \"%s\": Phase %d launched!"), *GetName(), currentlyAtIndex));
	SpawnNext();
}

void AActorTrigger_General::SpawnNext() {
	currentlyAtIndex++;
	if (currentlyAtIndex < EnemySpawns.Num()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Trigger \"%s\": Phase %d queued in %f seconds!"), *GetName(), currentlyAtIndex, EnemySpawns[currentlyAtIndex].SpawnDelay));
		if (EnemySpawns[currentlyAtIndex].SpawnDelay > 0)
			GetWorldTimerManager().SetTimer(this, &AActorTrigger_General::RunSpawn, EnemySpawns[currentlyAtIndex].SpawnDelay, true);
		else
			RunSpawn();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Trigger \"%s\": Last Phase %d done!"), *GetName(), currentlyAtIndex));
	}
}