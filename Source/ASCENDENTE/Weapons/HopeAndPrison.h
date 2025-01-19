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

	void StartShootPrimary();
	void StartShootSecondary();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *ShotgunSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Cooldown")
	float SecondaryFireRate = 0.05f;
	UPROPERTY(EditAnywhere, Category = "Expansive Shot")
	float ExpansiveCooldown = 3;
	UPROPERTY(EditAnywhere, Category = "Shotgun")
	float ShotgunRadius = 1.05f;
	UPROPERTY(EditAnywhere, Category = "Shotgun")
	float ShotgunDamage = 10;

	float CurrentFireRate;
	bool bExpansiveReady = true;

	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UPaperFlipbook *ShootFlipbook;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UPaperFlipbook *IdleFlipbook;

	void SetNextFire();
	void SetNextExpansive();

protected:
	virtual void ShootPrimary() override;
	virtual void ShootSecondary() override;
};
