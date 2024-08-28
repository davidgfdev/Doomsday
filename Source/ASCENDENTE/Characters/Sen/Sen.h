// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\Source\ASCENDENTE\Characters\BasicCharacter.h"
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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UCameraComponent *GetCameraComponent() const { return CameraComponent; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent *Weapon;

	UPROPERTY(EditAnywhere, Category = "Aim")
	float SensibilityX = 180;
	UPROPERTY(EditAnywhere, Category = "Aim")
	float SensibilityY = 160;
	UPROPERTY(EditAnywhere, Category = "Jump")
	float CoyoteSeconds = 0.3f;
	UPROPERTY(EditAnywhere, Category = "Jump")
	float BufferSeconds = 0.1f;
	UPROPERTY(EditAnywhere, Category = "Dash")
	float DashForceGround = 3000;
	UPROPERTY(EditAnywhere, Category = "Dash")
	float DashForceAir = 1300;
	UPROPERTY(EditAnywhere, Category = "Dash")
	float DashCooldownSeconds = 2;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TArray<TSubclassOf<class AWeaponBase>> Weapons;

	float CoyoteTime;
	float BufferTime;
	bool bCanDoubleJump = false;
	bool bCanDash = true;
	float DashForce;
	float MoveForwardAxisValue = 0;
	float StrafeAxisValue = 0;
	float OriginalMaxSpeed = 1000;

	void Aim(float Value);
	void Turn(float Value);
	void MoveForward(float Value);
	void Strafe(float Value);
	void PrimaryFire(float Value);
	void SecondaryFire(float Value);
	void StartJump();
	void StopJump();
	void Dash();
	void DashCooldown();
	void MidAirFire();
	void ChangeWeapon();
	void HPPrimaryFire();
	void HPSecondaryFire();

	APlayerController *SenPlayerController;

public:
	void SwitchMovementMode(bool bIsMoving);
};
