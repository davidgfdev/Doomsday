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
	virtual void ShootPrimary() override;
	virtual void ShootSecondary() override;
	virtual void ShootMidAir() override;

private:
	UPROPERTY(EditAnywhere, Category = "Cooldown")
	float SecondaryFireRate = 0.05f;

	float CurrentFireRate;
	bool bReadyToFire = true;

	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	void SetNextFire();
};
