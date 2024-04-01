// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "NewTypes.h"

#include "EscapeFromAncientCharacter.generated.h"


UCLASS(Blueprintable)
class AEscapeFromAncientCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEscapeFromAncientCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* NewInputComponent);

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EMovementState MovementState = EMovementState::Stand_State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FCharacterSpeed CharacterSpeed;

	UFUNCTION()
		void InputAxisX(float value);
	UFUNCTION()
		void InputAxisY(float value);

		float AxisX = 0.0f;
		float AxisY = 0.0f;

	UFUNCTION()
		void MovementTickMy(float deltaTime);

	UFUNCTION()
		void CharacterUpdate();
	UFUNCTION(BlueprintCallable)
		void ChangeMovementState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Stand = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Aim = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Walk = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Run = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Sprint = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed = 0.0f;
};

/*
Aim
Walk
Run
Sprint
WalkAim
RunAim
*/