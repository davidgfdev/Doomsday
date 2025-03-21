// Fill out your copyright notice in the Description page of Project Settings.

#include "Nihilist.h"
#include "..\Source\ASCENDENTE\Projectiles\ProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

void ANihilist::BeginPlay()
{
    Super::BeginPlay();
}

void ANihilist::ShootPrimary()
{
    if (bReadyToFire)
    {
        FHitResult Hit;
        ASen* Sen = Cast<ASen>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

        TArray<UCameraComponent*> CameraComps;
        Sen->GetComponents<UCameraComponent>(CameraComps);

        if (CameraComps.Num() > 0)
        {
            FVector TraceStart = CameraComps[0]->GetComponentLocation();
            FVector TraceEnd = TraceStart + UKismetMathLibrary::GetForwardVector(CameraComps[0]->GetComponentRotation()) * 5000;

            FCollisionQueryParams QueryParams;
            QueryParams.AddIgnoredActor(this);
            QueryParams.AddIgnoredActor(GetOwner());

            GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);
            OnEnemyConnect(TraceEnd);

            if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
            {
                if (GetOwner())
                {
                    auto MyOwnerInstigator = GetOwner()->GetInstigatorController();
                    auto DamageType = UDamageType::StaticClass();

                    if (MyOwnerInstigator && DamageType)
                    {
                        UGameplayStatics::ApplyDamage(Hit.GetActor(), FireDamage, MyOwnerInstigator, this, DamageType);
                    }
                }
            }
        }

        bReadyToFire = false;
        FTimerHandle Handle;
        GetWorldTimerManager().SetTimer(Handle, this, &ANihilist::SetNextFire, FireRate, false);

        UE_LOG(LogTemp, Display, TEXT("Nihilist: Primary"));
    }
}

void ANihilist::SetNextFire()
{
    bReadyToFire = true;
}