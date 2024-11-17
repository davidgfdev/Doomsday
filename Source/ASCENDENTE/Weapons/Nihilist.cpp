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
    CurrentFireRate = FireRate;
    if (bReadyToFire)
    {
        FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
        FRotator SpawnRotator = ProjectileSpawnPoint->GetComponentRotation();
        auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotator);
        Projectile->SetOwner(this);
        Projectile->Damage = FireDamage;
        bReadyToFire = false;
        FTimerHandle Handle;
        GetWorldTimerManager().SetTimer(Handle, this, &ANihilist::SetNextFire, CurrentFireRate, false);
    }
}

void ANihilist::ShootSecondary()
{
    if (bOrbReady)
    {
        bOrbReady = false;

        FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
        FRotator SpawnRotator = ProjectileSpawnPoint->GetComponentRotation();
        auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(OrbClass, SpawnLocation, SpawnRotator);
        Projectile->SetOwner(this);
        Projectile->Damage = FireDamage;

        FTimerHandle HandleOrbCooldown;
        GetWorldTimerManager().SetTimer(HandleOrbCooldown, this, &ANihilist::SetNextOrb, OrbCooldown, false);
    }
}

void ANihilist::SetNextFire()
{
    bReadyToFire = true;
}

void ANihilist::RecoverMovement()
{
    ASen *Player = Cast<ASen>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    Player->SwitchMovementMode(true);
}

void ANihilist::SetNextOrb()
{
    bOrbReady = true;
}