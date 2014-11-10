// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "samuraisenshi.h"
#include "samuraisenshiCharacter.h"

AsamuraisenshiCharacter::AsamuraisenshiCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Setup attributes
	CharacterAttributes = PCIP.CreateDefaultSubobject<UCharacterAttributesComponent>(this, TEXT("Character Attributes"));
	CharacterAttributes->AttachTo(RootComponent);

	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set size for collision capsule
	AttackPivot = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("AttackPivot"));
	AttackPivot->AttachTo(RootComponent);
	AttackPivot->bAbsoluteRotation = true;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Face in the direction we are moving..
	CharacterMovement->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->GravityScale = 2.f;
	CharacterMovement->AirControl = 0.80f;
	CharacterMovement->JumpZVelocity = 0.f;
	CharacterMovement->GroundFriction = 3.f;
	CharacterMovement->MaxWalkSpeed = 600.f;
	CharacterMovement->MaxFlySpeed = 600.f;
}

//////////////////////////////////////////////////////////////////////////
// Input
void AsamuraisenshiCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAxis("Move X", this, &AsamuraisenshiCharacter::Move);
}

void AsamuraisenshiCharacter::Move(float intensity)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f, -1.f, 0.f), intensity);
}