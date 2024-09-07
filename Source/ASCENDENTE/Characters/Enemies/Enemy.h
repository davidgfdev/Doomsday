// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\Source\ASCENDENTE\Characters\BasicCharacter.h"
#include "Enemy.generated.h"

/**
 *
 */
UCLASS()
class ASCENDENTE_API AEnemy : public ABasicCharacter
{
	GENERATED_BODY()

public:
	void MarkForAbsolution();

	bool bIsMarkedForAbsolution = false;

private:
	UPROPERTY(EditAnywhere, Category = "Absolution")
	int AbsolutionTime = 30;

	void DisableAbsolution();
};
