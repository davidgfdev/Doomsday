// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Dogmatist.generated.h"

/**
 *
 */
UCLASS()
class ASCENDENTE_API ADogmatist : public AEnemy
{
	GENERATED_BODY()

public:
	virtual void Attack() override;
	virtual void HandleDeath() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBlackboardLineOfFire();

	UPROPERTY(EditAnywhere, Category = "Aggro")
	float AttackRange = 300;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float Damage = 25;

	UPROPERTY(BlueprintReadOnly)
	bool isPlayerInLineOfFire = false;

	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectileBase> ProjectileClass;

private:
	void CheckLineOfFire();
};
