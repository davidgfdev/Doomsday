// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "NihilistProjectile.generated.h"

/**
 *
 */
UCLASS()
class ASCENDENTE_API ANihilistProjectile : public AProjectileBase
{
	GENERATED_BODY()

protected:
	virtual void ApplyHitEffects(FHitResult Hit);

private:
	UPROPERTY(EditDefaultsOnly, Category = "WeakPoint")
	TSubclassOf<AActor> WeakPointClass;
};
