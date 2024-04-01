// Copyright Epic Games, Inc. All Rights Reserved.

#include "EscapeFromAncientCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

AEscapeFromAncientCharacter::AEscapeFromAncientCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEscapeFromAncientCharacter::Tick(float DeltaSeconds)
{
	MovementTickMy(DeltaSeconds);

    Super::Tick(DeltaSeconds);

}

void AEscapeFromAncientCharacter::SetupPlayerInputComponent(UInputComponent* NewInputComponent)
{
	Super::SetupPlayerInputComponent(NewInputComponent);

	NewInputComponent->BindAxis(TEXT("MoveForward"), this, &AEscapeFromAncientCharacter::InputAxisX);
	NewInputComponent->BindAxis(TEXT("MoveRight"), this, &AEscapeFromAncientCharacter::InputAxisY);

}

void AEscapeFromAncientCharacter::InputAxisX(float value)
{
	AxisX = value;
}

void AEscapeFromAncientCharacter::InputAxisY(float value)
{
	AxisY = value;
}

void AEscapeFromAncientCharacter::MovementTickMy(float deltaTime)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), AxisX);
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), AxisY);

	APlayerController* myController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (myController)
	{
		FHitResult HitResult;

		myController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery6, false, HitResult);

		FRotator R = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitResult.Location);

		SetActorRotation(FQuat(FRotator(0.0f, R.Yaw, 0.0f)));
	}
}

void AEscapeFromAncientCharacter::CharacterUpdate()
{
	float ResSpeed = 800.0f;

	switch (MovementState)
	{
		case EMovementState::Stand_State:
			ResSpeed = CharacterSpeed.RunSpeed;
		break;
		case EMovementState::Aim_State:
			ResSpeed = CharacterSpeed.AimSpeed;
			break;
		case EMovementState::Walk_State:
			ResSpeed = CharacterSpeed.WalkSpeed;
			break;
		case EMovementState::WalkAim_State:
			ResSpeed = CharacterSpeed.WalkAimSpeed;
			break;
		case EMovementState::Run_State:
			ResSpeed = CharacterSpeed.RunSpeed;
			break;
		case EMovementState::RunAim_State:
			ResSpeed = CharacterSpeed.RunAimSpeed;
			break;
		case EMovementState::Sprint_State:
			ResSpeed = CharacterSpeed.SprintSpeed;
			break;
		default:
			break;
	}

	GetCharacterMovement()->MaxWalkSpeed = ResSpeed;
}

void AEscapeFromAncientCharacter::ChangeMovementState()
{
	if (Aim)
	{
		if (Speed == 0)
		{
			MovementState = EMovementState::Aim_State;
		}
		else
		{
			MovementState = EMovementState::RunAim_State;

			if (Walk)
			{
				MovementState = EMovementState::WalkAim_State;
			}
			else if (Run)
			{
				MovementState = EMovementState::RunAim_State;
			}
			else if (Sprint)
			{
				MovementState = EMovementState::Sprint_State;
			}
		}
	}
	else
	{
		if (Speed == 0)
		{
			MovementState = EMovementState::Stand_State;
		}
		else
		{
			MovementState = EMovementState::Run_State;

			if (Walk)
			{
				MovementState = EMovementState::Walk_State;
			}
			else if (Run)
			{
				MovementState = EMovementState::Run_State;
			}
			else if (Sprint)
			{
				MovementState = EMovementState::Sprint_State;
			}
			else
			{
				MovementState = EMovementState::Run_State;
			}
		}
	}

	CharacterUpdate();
}