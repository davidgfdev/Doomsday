// Fill out your copyright notice in the Description page of Project Settings.

#include "Faithful.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"
#include "Kismet/GameplayStatics.h"

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
    TArray<AActor *> IgnoreActors;
    IgnoreActors.Add(this);
    auto DamageType = UDamageType::StaticClass();
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, ProjectileSpawnPoint->GetComponentLocation(), AttackRadius, DamageType, IgnoreActors, this);
    DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), AttackRadius, 12, FColor::Red, false, 2);

    Super::Attack();
}

void AFaithful::CheckPlayerInRange()
{
    if (SenReference) 
    {
        FVector SenLocation = SenReference->GetActorLocation();
        float Distance = FVector::Distance(SenLocation, GetActorLocation());
        isPlayerInRange = (Distance < AttackRange);
    }
}

void AFaithful::HandleDeath() 
{
    Super::HandleDeath();
}