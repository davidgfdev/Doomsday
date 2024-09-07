// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ASCENDENTEGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class ASCENDENTE_API AASCENDENTEGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor *DeadActor);

protected:
	virtual void BeginPlay();

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:
	void MarkEnemies();
};
