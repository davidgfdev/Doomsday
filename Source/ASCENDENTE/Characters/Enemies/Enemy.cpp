// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

void AEnemy::MarkForAbsolution()
{
    DrawDebugSphere(GetWorld(), GetActorLocation(), 200, 12, FColor::Yellow, false, AbsolutionTime);
    bIsMarkedForAbsolution = true;

    FTimerHandle AbsolutionTimerHandler;
    GetWorldTimerManager().SetTimer(AbsolutionTimerHandler, this, &AEnemy::DisableAbsolution, AbsolutionTime, false);
}

void AEnemy::DisableAbsolution()
{
    bIsMarkedForAbsolution = false;
}
