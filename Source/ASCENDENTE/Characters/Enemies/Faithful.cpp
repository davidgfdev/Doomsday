// Fill out your copyright notice in the Description page of Project Settings.

#include "Faithful.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"

void AFaithful::BeginPlay()
{
    Super::BeginPlay();
}

void AFaithful::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckPlayerInRange();
    UpdateBlackboardPlayerInRange();
}

void AFaithful::Attack()
{
    UE_LOG(LogTemp, Display, TEXT("Atacando al jugador"));
}

void AFaithful::CheckPlayerInRange()
{
    FVector SenLocation = SenReference->GetActorLocation();
    float Distance = FVector::Distance(SenLocation, GetActorLocation());
    isPlayerInRange = (Distance < AttackRange);
}