// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "samuraisenshi.h"
#include "Character_General.h"

ACharacter_General::ACharacter_General(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
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

	// Setup attributes
	CharacterAttributes = PCIP.CreateDefaultSubobject<UComponent_CharacterAttributes>(this, TEXT("CharacterAttributes"));
	CharacterAttributes->AttachTo(RootComponent);
}

void ACharacter_General::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	
	DrawDebugLine(
		GetWorld(),
		FVector(GetActorLocation().X, -10000, DebugZ),
		FVector(GetActorLocation().X, 10000, DebugZ),
		FColor(255, 255, 255),
		false, -1, 0,
		12.333
	);
}

//////////////////////////////////////////////////////////////////////////
// Input
void ACharacter_General::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAxis("Move X", this, &ACharacter_General::Move);
}

void ACharacter_General::Move(float intensity)
{
	if (CallOnMove && abs(intensity) >= Sidestep_Deadzone)
	{
		OnMove(intensity);
		CallOnMove = false;
	}
	else if (!CallOnMove && abs(intensity) < Sidestep_Deadzone)
	{
		CallOnMove = true;
	}
	// add movement in that direction
	AddMovementInput(FVector(0.f, -1.f, 0.f), intensity);
}