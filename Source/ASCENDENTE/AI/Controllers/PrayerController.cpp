// Fill out your copyright notice in the Description page of Project Settings.


#include "PrayerController.h"

void APrayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (BTAsset)
    {
        RunBehaviorTree(BTAsset);
    }
}