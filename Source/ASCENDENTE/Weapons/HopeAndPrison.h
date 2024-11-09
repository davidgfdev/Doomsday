// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "HopeAndPrison.generated.h"

/**
 *
 */
UCLASS()
class ASCENDENTE_API AHopeAndPrison : public AWeaponBase
{
	GENERATED_BODY()

public:
	AHopeAndPrison();

	void StartShootPrimary(float &Ammo);
	void StartShootSecondary(float &Ammo);
	void StartShootMidAir(float &Ammo);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *ShotgunSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Cooldown")
	float SecondaryFireRate = 0.05f;
	UPROPERTY(EditAnywhere, Category = "Expansive Shot")
	float ExpansiveCooldown = 3;
	UPROPERTY(EditAnywhere, Category = "Expansive Shot")
	float ExpansiveRadius = 3;
	UPROPERTY(EditAnywhere, Category = "Expansive Shot")
	float ExpansiveImpulse = 300;
	UPROPERTY(EditAnywhere, Category = "Expansive Shot")
	float ExpansiveRepelForce = 500;
	UPROPERTY(EditAnywhere, Category = "Shotgun")
	float ShotgunRadius = 1.05f;
	UPROPERTY(EditAnywhere, Category = "Shotgun")
	float ShotgunDamage = 10;

	float CurrentFireRate;
	bool bReadyToFire = true;
	bool bExpansiveReady = true;

	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UPaperFlipbook *ShootFlipbook;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UPaperFlipbook *IdleFlipbook;

	void SetNextFire();
	void SetNextExpansive();

protected:
	virtual void ShootPrimary(float &Ammo) override;
	virtual void ShootSecondary(float &Ammo) override;
	virtual void ShootMidAir(float &Ammo) override;
};
