// Fill out your copyright notice in the Description page of Project Settings.

#include "HopeAndPrison.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"

void AHopeAndPrison::ShootPrimary()
{
    CurrentFireRate = FireRate;
    if (bReadyToFire)
    {
        FHitResult Hit;
        ASen *Sen = Cast<ASen>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

        FVector TraceStart = Sen->GetCameraComponent()->GetComponentLocation();
        FVector TraceEnd = UKismetMathLibrary::GetForwardVector(Sen->GetCameraComponent()->GetComponentRotation()) * 5000;

        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(this);

        GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);
        DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Orange, false, 3, 0, 1.5f);

        if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
        {
            UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
        }

        bReadyToFire = false;
        FTimerHandle Handle;
        GetWorldTimerManager().SetTimer(Handle, this, &AHopeAndPrison::SetNextFire, CurrentFireRate, false);

        UE_LOG(LogTemp, Display, TEXT("Hope & Prison: Primary"));
    }
}
void AHopeAndPrison::ShootSecondary()
{
    CurrentFireRate = SecondaryFireRate;
    UE_LOG(LogTemp, Display, TEXT("Hope & Prison: Secondary"));
}
void AHopeAndPrison::ShootMidAir()
{
    UE_LOG(LogTemp, Display, TEXT("Hope & Prison: ShootMidAir"));
    if (bExpansiveReady)
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
            UE_LOG(LogTemp, Display, TEXT("Enemy detected"));
        }

        FTimerHandle HandleExpansiveCooldown;
        GetWorldTimerManager().SetTimer(HandleExpansiveCooldown, this, &AHopeAndPrison::SetNextExpansive, ExpansiveCooldown, false);
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