// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Nihilist.generated.h"

/**
 *
 */
UCLASS()
class ASCENDENTE_API ANihilist : public AWeaponBase
{
	GENERATED_BODY()

public:
	void RecoverMovement();

	void StartShootPrimary();
	void StartShootSecondary();

protected:
	virtual void BeginPlay() override;

	virtual void ShootPrimary() override;
	virtual void ShootSecondary() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectileBase> OrbClass;

	UPROPERTY(EditAnywhere, Category = "Secondary Mode")
	float RecoverMovementTime = 0.2;
	UPROPERTY(EditAnywhere, Category = "Cooldown")
	float OrbCooldown = 8;

	float CurrentFireRate;
	bool bOrbReady = true;

	void SetNextFire();
	void SetNextOrb();
};
