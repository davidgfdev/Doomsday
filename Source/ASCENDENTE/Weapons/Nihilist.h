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

	void StartShootPrimary();

protected:
	virtual void BeginPlay() override;

	virtual void ShootPrimary() override;

private:
	void SetNextFire();

	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;
};
