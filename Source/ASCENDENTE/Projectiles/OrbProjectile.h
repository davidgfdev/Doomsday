// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "OrbProjectile.generated.h"

/**
 *
 */
UCLASS()
class ASCENDENTE_API AOrbProjectile : public AProjectileBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Self-Destruction")
	float SecondsToExplode = 5;
	UPROPERTY(EditAnywhere, Category = "Self-Destruction")
	float OrbScaleFactor = 1.07f;
	UPROPERTY(EditAnywhere, Category = "Self-Destruction")
	float MaxOrbScale = 8.0f;

	UFUNCTION()
	void DamageTaken(AActor *DamagedActor, float DamageRecieved, const UDamageType *DamageType, class AController *InstigatorController, AActor *DamageCauser);

	void Explode();
};
