// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "Engine.h"
#include "ActorTrigger_Boss.h"
#include "GameMode_General.h"


AActorTrigger_Boss::AActorTrigger_Boss(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	CanBeTriggered = true;

	CurrentPhase = BossTriggerPhase_Idle;
	TransitionStartAt = 0.0f;
	TransitionCurrentAt = 0.0f;
	TransitionDuration = 1.0f;

	// Create a camera and attach to boom
	SceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	// Create a camera and attach to boom
	CameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
	CameraComponent->AttachTo(SceneComponent);
	CameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
}

void AActorTrigger_Boss::BeginPlay()
{
	Super::BeginPlay();

	if (BossSpawner == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Error: No enemyspawn set on boss-trigger %s!"), *this->GetName()));
		return;
	}


	PlayerCharacter = Cast<ACharacter_General>(GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator());

	AbsoluteEndCameraPosition = CameraComponent->GetComponentLocation();

	// find the launching trigger
	TArray<UShapeComponent*, FDefaultAllocator> PossibleShapes;
	GetComponents<UShapeComponent>(PossibleShapes);

	bool MoreThanOneTrigger = false;
	for (TArray<UShapeComponent*>::TConstIterator ShapeIterator(PossibleShapes); ShapeIterator; ++ShapeIterator) {
		if (MoreThanOneTrigger) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Warning: More than one trigger set on %s!"), *this->GetName()));
			break;
		}
		
		TriggerComponent = *ShapeIterator;

		MoreThanOneTrigger = true;
	}
}

void AActorTrigger_Boss::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (PlayerCharacter == NULL || TriggerComponent == NULL)
		return;

	switch (CurrentPhase) {
		case BossTriggerPhase_Idle:
			if (GEngine)
			{
				AbsoluteStartCameraPosition = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager->ViewTarget.POV.Location;
				AbsoluteCurrentCameraPosition = AbsoluteStartCameraPosition;
			}
			break;
		case BossTriggerPhase_EnteredTrigger:
			CanBeTriggered = false;

			TransitionStartAt = GetWorld()->RealTimeSeconds - deltaTime;

			GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this, 0.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);

			CurrentPhase = BossTriggerPhase_FadingToBossCamera;
		case BossTriggerPhase_FadingToBossCamera:
			TransitionCurrentAt = (GetWorld()->RealTimeSeconds - TransitionStartAt) / TransitionDuration;
			AbsoluteCurrentCameraPosition = FMath::Lerp(AbsoluteStartCameraPosition, AbsoluteEndCameraPosition, FMath::Min(TransitionCurrentAt, 1.0f));
			break;
		case BossTriggerPhase_Spawning:
			BossSpawner->DoSpawn();
			CurrentPhase = BossTriggerPhase_Fighting;
			break;
		case BossTriggerPhase_FightOver:
			TransitionStartAt = GetWorld()->RealTimeSeconds;
			CurrentPhase = BossTriggerPhase_FadingToRegularCamera;
			break;
		case BossTriggerPhase_FadingToRegularCamera:
			AbsoluteStartCameraPosition = PlayerCharacter->SideViewCameraComponent->GetComponentLocation();
			TransitionCurrentAt = (GetWorld()->RealTimeSeconds - TransitionStartAt) / TransitionDuration;
			AbsoluteCurrentCameraPosition = FMath::Lerp(AbsoluteEndCameraPosition, AbsoluteStartCameraPosition, FMath::Min(TransitionCurrentAt, 1.0f));
			if (TransitionCurrentAt >= 1.0f)
			{
				CurrentPhase = BossTriggerPhase_Idle;
				GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(PlayerCharacter, 0.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
			}
			break;
	}

	CameraComponent->SetWorldLocation(AbsoluteCurrentCameraPosition);
}

void AActorTrigger_Boss::ReceiveActorBeginOverlap(AActor* OtherActor)
{
	if (BossSpawner != NULL)
	{
		if (Cast<ACharacter_General>(OtherActor))
		{
			Cast<AGameMode_General>(GetWorld()->GetAuthGameMode())->ToggleBoss(this);
			CurrentPhase = BossTriggerPhase_EnteredTrigger;
		}
	}
}