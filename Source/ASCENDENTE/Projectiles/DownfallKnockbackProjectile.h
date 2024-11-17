// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "DownfallKnockbackProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ASCENDENTE_API ADownfallKnockbackProjectile : public AProjectileBase
{
	GENERATED_BODY()
	
protected:
	virtual void ApplyHitEffects(FHitResult Hit) override;

private:
	void Explode();

	UPROPERTY(EditAnywhere, Category = "Explosion")
	int SecondsToExplode = 1;

	UPROPERTY(EditAnywhere, Category = "Explosion")
	float ExpansiveImpulse = 200;

	UPROPERTY(EditAnywhere, Category = "Explosion")
	float ExpansiveRadius = 1000;
};
