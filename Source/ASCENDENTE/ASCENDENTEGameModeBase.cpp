// Fill out your copyright notice in the Description page of Project Settings.

#include "ASCENDENTEGameModeBase.h"

void AASCENDENTEGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    StartGame();
}

void AASCENDENTEGameModeBase::ActorDied(AActor *DeadActor)
{
    DeadActor->Destroy();
}
