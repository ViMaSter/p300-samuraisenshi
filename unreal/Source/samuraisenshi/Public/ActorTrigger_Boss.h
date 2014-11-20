// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Character_General.h"
#include "ActorTrigger_Boss.generated.h"

/**
 * 
 */
UCLASS()
class SAMURAISENSHI_API AActorTrigger_Boss : public AActor
{
	GENERATED_UCLASS_BODY()

	/* Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class USceneComponent> SceneComponent;

	/* Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class UCameraComponent> CameraComponent;

	UShapeComponent* TriggerComponent;

	/* Defaults */
	ACharacter_General* PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Camera)
	FVector AbsoluteStartCameraPosition;

	UPROPERTY(BlueprintReadOnly, Category = Camera)
	FVector AbsoluteCurrentCameraPosition;

	UPROPERTY(BlueprintReadOnly, Category = Camera)
	FVector AbsoluteEndCameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float TransitionDuration;

	float TransitionStartAt;
	float TransitionCurrentAt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	bool CanBeTriggered;

	UPROPERTY(BlueprintReadWrite, Category = Camera)
	int32 CurrentPhase;

	void BeginPlay();

	virtual void Tick(float deltaTime) override;
};