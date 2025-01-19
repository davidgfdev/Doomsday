// Fill out your copyright notice in the Description page of Project Settings.

#include "Prayer.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"
#include "..\Source\ASCENDENTE\Projectiles\ProjectileBase.h"

void APrayer::BeginPlay()
{
    Super::BeginPlay();
}

void APrayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckPlayerInRange();
}

void APrayer::Attack()
{
    Super::Attack();

    FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
    FRotator SpawnRotator = ProjectileSpawnPoint->GetComponentRotation();
    auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotator);
    Projectile->SetOwner(this);
    Projectile->Damage = Damage;
}

void APrayer::CheckPlayerInRange()
{
    FVector SenLocation = SenReference->GetActorLocation();
    float Distance = FVector::Distance(SenLocation, GetActorLocation());
}

void APrayer::HandleDeath()
{
    Super::HandleDeath();
}