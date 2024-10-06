// Fill out your copyright notice in the Description page of Project Settings.

#include "Nihilist.h"
#include "..\Source\ASCENDENTE\Projectiles\ProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"

void ANihilist::BeginPlay()
{
    Super::BeginPlay();
}

void ANihilist::ShootPrimary(float &Ammo)
{
    CurrentFireRate = FireRate;
    if (bReadyToFire && Ammo >= PrimaryAmmoCost)
    {
        FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
        FRotator SpawnRotator = ProjectileSpawnPoint->GetComponentRotation();
        auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotator);
        Projectile->SetOwner(this);
        Projectile->Damage = FireDamage;
        bReadyToFire = false;
        FTimerHandle Handle;
        GetWorldTimerManager().SetTimer(Handle, this, &ANihilist::SetNextFire, CurrentFireRate, false);
        Ammo -= PrimaryAmmoCost;
    }
}

void ANihilist::ShootSecondary(float &Ammo)
{
    CurrentFireRate = SecondaryFireRate;
    ASen *Player = Cast<ASen>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    Player->SwitchMovementMode(false);
    if (bReadyToFire && Ammo >= SecondaryAmmoCost)
    {
        bReadyToFire = false;

        FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
        FRotator SpawnRotator = ProjectileSpawnPoint->GetComponentRotation();
        auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotator);
        Projectile->SetOwner(this);
        Projectile->Damage = FireDamage;

        FTimerHandle HandleNextFire;
        GetWorldTimerManager().SetTimer(HandleNextFire, this, &ANihilist::SetNextFire, CurrentFireRate, false);
        Ammo -= SecondaryAmmoCost;
    }
}

void ANihilist::ShootMidAir(float &Ammo)
{
    if (bOrbReady && Ammo >= MidAirAmmoCost)
    {
        bOrbReady = false;

        FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
        FRotator SpawnRotator = ProjectileSpawnPoint->GetComponentRotation();
        auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(OrbClass, SpawnLocation, SpawnRotator);
        Projectile->SetOwner(this);
        Projectile->Damage = FireDamage;

        FTimerHandle HandleOrbCooldown;
        GetWorldTimerManager().SetTimer(HandleOrbCooldown, this, &ANihilist::SetNextOrb, OrbCooldown, false);
        Ammo -= MidAirAmmoCost;
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