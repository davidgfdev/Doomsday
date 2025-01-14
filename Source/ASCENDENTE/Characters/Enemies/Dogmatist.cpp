// Fill out your copyright notice in the Description page of Project Settings.

#include "Dogmatist.h"
#include "Kismet/KismetSystemLibrary.h"
#include "..\Source\ASCENDENTE\Projectiles\ProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"

void ADogmatist::BeginPlay()
{
    Super::BeginPlay();
}

void ADogmatist::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckLineOfFire();
    UpdateBlackboardLineOfFire();
}

void ADogmatist::Attack()
{
    Super::Attack();

    FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
    FRotator SpawnRotator = ProjectileSpawnPoint->GetComponentRotation();
    auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotator);
    Projectile->SetOwner(this);
    Projectile->Damage = Damage;
}

void ADogmatist::HandleDeath()
{
    Super::HandleDeath();
}

void ADogmatist::CheckLineOfFire()
{
    FVector TraceEnd = SenReference->GetActorLocation();
    FVector TraceStart = GetActorLocation();

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    FHitResult Hit;

    GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

    isPlayerInLineOfFire = (Hit.bBlockingHit && IsValid(Hit.GetActor()));
}
