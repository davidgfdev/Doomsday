// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Tree.generated.h"

/**
 * 
 */
UCLASS()
class ASCENDENTE_API ATree : public AEnemy
{
	GENERATED_BODY()

protected:
	virtual void HandleDeath() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void EndGame();
};
