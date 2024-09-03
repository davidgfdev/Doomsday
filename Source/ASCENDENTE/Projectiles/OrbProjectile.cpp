// Fill out your copyright notice in the Description page of Project Settings.

#include "OrbProjectile.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

void AOrbProjectile::BeginPlay()
{
    FTimerHandle AutoDestructionTimeHandle;
    GetWorldTimerManager().SetTimer(AutoDestructionTimeHandle, this, &AOrbProjectile::Explode, SecondsToExplode, false);

    OnTakeAnyDamage.AddDynamic(this, &AOrbProjectile::DamageTaken);

    Super::BeginPlay();
}

void AOrbProjectile::Explode()
{
    FVector ProjectileCurrentScale = ProjectileMesh->GetComponentScale();
    DrawDebugSphere(GetWorld(), GetActorLocation(), UKismetMathLibrary::Vector4_Size(ProjectileCurrentScale) * 85, 12, FColor::Red, false, 2.f);
    auto DamageType = UDamageType::StaticClass();
    TArray<AActor *> IgnoreActors;
    IgnoreActors.Add(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), UKismetMathLibrary::Vector4_Size(ProjectileCurrentScale) * 85, DamageType, IgnoreActors, GetOwner());
    Destroy();
}

void AOrbProjectile::DamageTaken(AActor *DamagedActor, float DamageRecieved, const UDamageType *DamageType, class AController *InstigatorController, AActor *DamageCauser)
{
    UE_LOG(LogTemp, Display, TEXT("Recibo daño, soy el orbe"));
    FVector ProjectileCurrentScale = ProjectileMesh->GetComponentScale();
    FVector ProjectileIncreasedScale = ProjectileCurrentScale * OrbScaleFactor;
    ProjectileMesh->SetWorldScale3D(ProjectileIncreasedScale);

    if (UKismetMathLibrary::Vector4_Size(ProjectileIncreasedScale) > MaxOrbScale)
    {
        Explode();
    }
}
