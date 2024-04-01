// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NewTypes.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Stand_State UMETA(DisplayName = "Stand State"),
	Aim_State UMETA(DisplayName = "Aim State"),

	Walk_State UMETA(DisplayName = "Walk State"),
	WalkAim_State UMETA(DisplayName = "Walk Aim State"),

	Run_State UMETA(DisplayName = "Run State"),
	RunAim_State UMETA(DisplayName = "Run Aim State"),

	Sprint_State UMETA(DisplayName = "Sprint State")
};

USTRUCT(BlueprintType)
struct FCharacterSpeed
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AimSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WalkAimSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WalkSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RunAimSpeed = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RunSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SprintSpeed = 800.0f;
};

UCLASS()
class ESCAPEFROMANCIENT_API UNewTypes: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
