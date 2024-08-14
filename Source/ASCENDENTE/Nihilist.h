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
	virtual void ShootPrimary() override;
	virtual void ShootSecondary() override;
	virtual void ShootMidAir() override;
};
