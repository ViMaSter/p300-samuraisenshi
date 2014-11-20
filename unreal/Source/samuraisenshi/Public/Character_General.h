// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Component_CharacterAttributes.h"
#include "Character_General.generated.h"

UCLASS()
class ACharacter_General : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class UCameraComponent> SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class USceneComponent> AttackPivot;

	/** General attributes every character in our game shares */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TSubobjectPtr<class UComponent_CharacterAttributes> CharacterAttributes;

protected:

	/** Called for side to side input */
	void Move(float intensity);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

};