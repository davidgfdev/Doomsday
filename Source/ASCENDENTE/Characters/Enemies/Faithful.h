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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBlackboardPlayerInRange();

	UPROPERTY(EditAnywhere, Category = "Aggro")
	float AttackRange = 300;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool isPlayerInRange = false;

private:
	void CheckPlayerInRange();
};
