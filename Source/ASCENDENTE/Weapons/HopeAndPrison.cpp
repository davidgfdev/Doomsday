// Fill out your copyright notice in the Description page of Project Settings.

#include "HopeAndPrison.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "TimerManager.h"
#include <ASCENDENTE/Projectiles/ProjectileBase.h>

AHopeAndPrison::AHopeAndPrison()
{
    ShotgunSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Shotgun SpawnPoint"));
    ShotgunSpawnPoint->SetupAttachment(WeaponFlipbook);
}

void AHopeAndPrison::ShootPrimary()
{
    CurrentFireRate = FireRate;
    if (bReadyToFire)
    {
        FHitResult Hit;
        ASen *Sen = Cast<ASen>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

        TArray<UCameraComponent *> CameraComps;
        Sen->GetComponents<UCameraComponent>(CameraComps);

        if (CameraComps.Num() > 0)
        {
            FVector TraceStart = CameraComps[0]->GetComponentLocation();
            FVector TraceEnd = TraceStart + UKismetMathLibrary::GetForwardVector(CameraComps[0]->GetComponentRotation()) * 5000;

            FCollisionQueryParams QueryParams;
            QueryParams.AddIgnoredActor(this);
            QueryParams.AddIgnoredActor(GetOwner());

            GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

            if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
            {
                auto MyOwnerInstigator = GetOwner()->GetInstigatorController();
                auto DamageType = UDamageType::StaticClass();

                UGameplayStatics::ApplyDamage(Hit.GetActor(), FireDamage, MyOwnerInstigator, this, DamageType);
            }
        }

        bReadyToFire = false;
        FTimerHandle Handle;
        GetWorldTimerManager().SetTimer(Handle, this, &AHopeAndPrison::SetNextFire, CurrentFireRate, false);

        UE_LOG(LogTemp, Display, TEXT("Hope & Prison: Primary"));
    }
}

void AHopeAndPrison::SetNextFire()
{
    bReadyToFire = true;
}

void AHopeAndPrison::SetNextExpansive()
{
    bExpansiveReady = true;
}