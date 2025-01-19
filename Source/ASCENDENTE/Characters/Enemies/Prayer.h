// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Prayer.generated.h"

/**
 * 
 */
UCLASS()
class ASCENDENTE_API APrayer : public AEnemy
{
	GENERATED_BODY()

public:
	virtual void Attack() override;
	virtual void HandleDeath() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Aggro")
	float AttackRange = 300;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float Damage = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectileBase> ProjectileClass;

private:
	void CheckPlayerInRange();
};
