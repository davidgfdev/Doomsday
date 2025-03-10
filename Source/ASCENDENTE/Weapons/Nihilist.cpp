// Fill out your copyright notice in the Description page of Project Settings.

#include "Nihilist.h"
#include "..\Source\ASCENDENTE\Projectiles\ProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"

void ANihilist::BeginPlay()
{
    Super::BeginPlay();
}

void ANihilist::ShootPrimary()
{
    if (bReadyToFire)
    {
        FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
        FRotator SpawnRotator = ProjectileSpawnPoint->GetComponentRotation();
        auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotator);
        Projectile->SetOwner(this);
        Projectile->Damage = FireDamage;
        bReadyToFire = false;
        FTimerHandle Handle;
        GetWorldTimerManager().SetTimer(Handle, this, &ANihilist::SetNextFire, FireRate, false);
    }
}

void ANihilist::SetNextFire()
{
    bReadyToFire = true;
}

void ANihilist::SetNextOrb()
{
    bOrbReady = true;
}