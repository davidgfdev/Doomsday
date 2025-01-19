// Fill out your copyright notice in the Description page of Project Settings.

#include "DogmtistController.h"

void ADogmtistController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    if (BTAsset)
    {
        RunBehaviorTree(BTAsset);
    }
}