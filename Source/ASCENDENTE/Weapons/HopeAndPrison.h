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

	void StartShootPrimary();

private:
	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UPaperFlipbook *ShootFlipbook;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UPaperFlipbook *IdleFlipbook;

	void SetNextFire();

protected:
	virtual void ShootPrimary() override;
};
