// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "Sen.generated.h"

/**
 *
 */
UCLASS()
class ASCENDENTE_API ASen : public ABasicCharacter
{
	GENERATED_BODY()

public:
	ASen();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Aim")
	float SensibilityX = 180;
	UPROPERTY(EditAnywhere, Category = "Aim")
	float SensibilityY = 160;

	void Aim(float Value);
	void Turn(float Value);
	void MoveForward(float Value);
	void Strafe(float Value);

	APlayerController *SenPlayerController;
};
