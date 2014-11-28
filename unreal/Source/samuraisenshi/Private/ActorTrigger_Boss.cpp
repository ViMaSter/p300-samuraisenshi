// Fill out your copyright notice in the Description page of Project Settings.

#include "samuraisenshi.h"
#include "Engine.h"
#include "ActorTrigger_Boss.h"


AActorTrigger_Boss::AActorTrigger_Boss(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	CanBeTriggered = true;

	CurrentPhase = 0;
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

	if (CurrentPhase != 0)
		return;

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
		else {
			TriggerComponent = *ShapeIterator;
		}

		MoreThanOneTrigger = true;
	}
}

void AActorTrigger_Boss::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (PlayerCharacter == NULL || TriggerComponent == NULL)
		return;

	switch (CurrentPhase) {
		case 0:
			if (GEngine)
			{
				AbsoluteStartCameraPosition = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager->ViewTarget.POV.Location;
				AbsoluteCurrentCameraPosition = AbsoluteStartCameraPosition;
			}
			break;
		case 1:
			TransitionStartAt = GetWorld()->RealTimeSeconds - deltaTime;
			CurrentPhase++;
			GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this, 0.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
		case 2:
			TransitionCurrentAt = (GetWorld()->RealTimeSeconds - TransitionStartAt) / TransitionDuration;
			AbsoluteCurrentCameraPosition = FMath::Lerp(AbsoluteStartCameraPosition, AbsoluteEndCameraPosition, FMath::Min(TransitionCurrentAt, 1.0f));
			if (TransitionCurrentAt >= 1.0f)
			{
				CurrentPhase++;
			}
			break;
		case 4:
			TransitionStartAt = GetWorld()->RealTimeSeconds;
			CurrentPhase++;
			break;
		case 5:
			AbsoluteStartCameraPosition = PlayerCharacter->SideViewCameraComponent->GetComponentLocation();
			TransitionCurrentAt = (GetWorld()->RealTimeSeconds - TransitionStartAt) / TransitionDuration;
			AbsoluteCurrentCameraPosition = FMath::Lerp(AbsoluteEndCameraPosition, AbsoluteStartCameraPosition, FMath::Min(TransitionCurrentAt, 1.0f));
			if (TransitionCurrentAt >= 1.0f)
			{
				CurrentPhase = 0;
				GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(PlayerCharacter, 0.0f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
			}
			break;
	}

	if (CurrentPhase > 0 && CurrentPhase < 2) {

	}

	CameraComponent->SetWorldLocation(AbsoluteCurrentCameraPosition);
}

void AActorTrigger_Boss::ToggleCamera()
{
	if (CanBeTriggered && CurrentPhase == 0)
		CurrentPhase++;
}