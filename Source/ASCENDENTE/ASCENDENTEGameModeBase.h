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

	FVector RespawnLocation = FVector(0,0,0);

protected:
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable)
	void SetRespawnLocation(FVector NewRespawnLocation) { RespawnLocation = NewRespawnLocation; }

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
};
