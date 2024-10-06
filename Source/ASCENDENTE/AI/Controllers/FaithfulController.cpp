// Fill out your copyright notice in the Description page of Project Settings.

#include "FaithfulController.h"

void AFaithfulController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    if (BTAsset)
    {
        RunBehaviorTree(BTAsset);
    }
}