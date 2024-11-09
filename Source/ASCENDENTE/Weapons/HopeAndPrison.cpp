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

AHopeAndPrison::AHopeAndPrison()
{
    ShotgunSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Shotgun SpawnPoint"));
    ShotgunSpawnPoint->SetupAttachment(ProjectileSpawnPoint);
}

void AHopeAndPrison::ShootPrimary(float &Ammo)
{
    CurrentFireRate = FireRate;
    if (bReadyToFire && Ammo >= PrimaryAmmoCost)
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
        Ammo -= PrimaryAmmoCost;
    }
}

void AHopeAndPrison::ShootSecondary(float &Ammo)
{
    CurrentFireRate = SecondaryFireRate;
    if (bReadyToFire && Ammo >= SecondaryFireRate)
    {
        bReadyToFire = false;
        FTimerHandle Handle;
        GetWorldTimerManager().SetTimer(Handle, this, &AHopeAndPrison::SetNextFire, CurrentFireRate, false);

        TArray<AActor *> IgnoreActors;
        IgnoreActors.Add(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
        auto DamageType = UDamageType::StaticClass();
        UGameplayStatics::ApplyRadialDamage(GetWorld(), ShotgunDamage, ShotgunSpawnPoint->GetComponentLocation(), ShotgunRadius, DamageType, IgnoreActors, GetOwner());

        DrawDebugSphere(GetWorld(), ShotgunSpawnPoint->GetComponentLocation(), ShotgunRadius, 12, FColor::Red, false, 2.f);

        UE_LOG(LogTemp, Display, TEXT("Hope & Prison: Secondary"));
        Ammo -= SecondaryAmmoCost;
    }
}

void AHopeAndPrison::ShootMidAir(float &Ammo)
{
    UE_LOG(LogTemp, Display, TEXT("Hope & Prison: StartShootMidAir"));
    if (bExpansiveReady && Ammo >= MidAirAmmoCost)
    {
        bExpansiveReady = false;

        TArray<AActor *> EnemiesInRange;
        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
        TArray<AActor *> ActorsToIgnore;
        ActorsToIgnore.Add(GetOwner());

        Cast<ACharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->LaunchCharacter(-UKismetMathLibrary::GetForwardVector(GetActorRotation()) * ExpansiveImpulse, false, true);

        UKismetSystemLibrary::SphereOverlapActors(GetWorld(),
                                                  ProjectileSpawnPoint->GetComponentLocation(),
                                                  ExpansiveRadius,
                                                  ObjectTypes,
                                                  ACharacter::StaticClass(),
                                                  ActorsToIgnore,
                                                  EnemiesInRange);

        DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), ExpansiveRadius, 12, FColor::Red, false, 2.f);

        for (int i = 0; i < EnemiesInRange.Num(); i++)
        {
            ACharacter *Enemy = Cast<ACharacter>(EnemiesInRange[i]);
            FVector ProjectedPlayerLocation = GetActorLocation();
            ProjectedPlayerLocation.Z = Enemy->GetActorLocation().Z;
            FVector DirectionFromPlayer = ProjectedPlayerLocation - Enemy->GetActorLocation();
            Enemy->LaunchCharacter(DirectionFromPlayer * ExpansiveRepelForce, false, false);
            auto MyOwnerInstigator = GetOwner()->GetInstigatorController();
            auto DamageType = UDamageType::StaticClass();
            UGameplayStatics::ApplyDamage(Enemy, ShotgunDamage, MyOwnerInstigator, GetOwner(), DamageType);
            UE_LOG(LogTemp, Display, TEXT("Enemy detected"));
        }

        FTimerHandle HandleExpansiveCooldown;
        GetWorldTimerManager().SetTimer(HandleExpansiveCooldown, this, &AHopeAndPrison::SetNextExpansive, ExpansiveCooldown, false);

        Ammo -= MidAirAmmoCost;
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