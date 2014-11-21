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

	FVector AbsoluteStartCameraPosition;
	FVector AbsoluteCurrentCameraPosition;
	FVector AbsoluteEndCameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float TransitionDuration;

	float TransitionStartAt;
	float TransitionCurrentAt;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	int32 CurrentPhase;

	// Variable that can be used to disable the triggerzone (i.e. still remaining enemies)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	bool CanBeTriggered;


	void BeginPlay();
	virtual void Tick(float deltaTime) override;


	UFUNCTION(BlueprintCallable, Category = Camera)
	void ToggleCamera();
};