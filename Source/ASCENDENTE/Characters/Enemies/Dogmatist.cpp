// Fill out your copyright notice in the Description page of Project Settings.

#include "Dogmatist.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"

void ADogmatist::BeginPlay()
{
    Super::BeginPlay();
}

void ADogmatist::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckPlayerInRange();
    UpdateBlackboardPlayerInRange();
}

void ADogmatist::Attack()
{
    Super::Attack();
}

void ADogmatist::HandleDeath()
{
    Super::HandleDeath();
}

void ADogmatist::CheckPlayerInRange()
{
    FVector SenLocation = SenReference->GetActorLocation();
    float Distance = FVector::Distance(SenLocation, GetActorLocation());
    isPlayerInRange = (Distance < AttackRange);
}