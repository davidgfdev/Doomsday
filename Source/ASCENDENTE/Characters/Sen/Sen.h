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

	void HandleDeath();

	void AddAscensionKills();

	class UCameraComponent *GetCameraComponent() const { return CameraComponent; }

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAmmo(float Ammo);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAscendPanel(bool isVisible);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCrosshairSize(float Speed);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *WeaponArmComponent;

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
	UPROPERTY(EditAnywhere, Category = "Ammo")
	float MaxAmmo = 100;
	UPROPERTY(EditAnywhere, Category = "Absolution")
	float AmmoPerAbsolution = 50;
	UPROPERTY(EditAnywhere, Category = "Absolution")
	float AbsolutionDamage = 30;
	UPROPERTY(EditAnywhere, Category = "Ascension")
	float TimeBetweenAscensions = 150;
	UPROPERTY(EditAnywhere, Category = "Ascension")
	float AscensionDuration = 20;
	UPROPERTY(EditAnywhere, Category = "Ascension")
	float AscensionExtraDamagePercent = 1.70;
	UPROPERTY(EditAnywhere, Category = "Ascension")
	float AscensionBuffDuration = 60;
	UPROPERTY(EditAnywhere, Category = "Ascension")
	float AscensionHealth = 70;
	UPROPERTY(EditAnywhere, Category = "Headbob")
	float HeadbobFactor = 1;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TArray<TSubclassOf<class AWeaponBase>> Weapons;

	UPROPERTY(EditAnywhere, Category = "Headbob")
	TSubclassOf<class ULegacyCameraShake> HeadBobCameraShake;

	float CoyoteTime;
	float BufferTime;
	bool bCanDoubleJump = false;
	bool bCanDash = true;
	float DashForce;
	float MoveForwardAxisValue = 0;
	float StrafeAxisValue = 0;
	float OriginalMaxSpeed = 1000;
	float CurrentAmmo = 100;
	bool bCanAscend = true;
	bool bIsAscending = false;
	int AscensionKills = 0;

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
	void ChangeWeapon();
	void HPPrimaryFire();
	void HPSecondaryFire();
	void Absolution();
	void Ascend();
	void AscensionCooldown();
	void DisableAscension();
	void AscendanceEnd();
	void HeadBob();
	void Respawn();

	APlayerController *SenPlayerController;

	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_WorldDynamic;

public:
	void SwitchMovementMode(bool bIsMoving);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealth(float Health);
};
