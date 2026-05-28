// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Faithful.generated.h"

/**
 *
 */
UCLASS()
class ASCENDENTE_API AFaithful : public AEnemy
{
	GENERATED_BODY()

public:
	virtual void Attack() override;
	virtual void HandleDeath() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBlackboardPlayerInRange();

	UPROPERTY(EditAnywhere, Category = "Aggro")
	float AttackRange = 300;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool isPlayerInRange = false;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float Damage = 25;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float AttackRadius = 60;

private:
	void CheckPlayerInRange();
};
