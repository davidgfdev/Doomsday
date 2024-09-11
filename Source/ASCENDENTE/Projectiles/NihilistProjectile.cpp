// Fill out your copyright notice in the Description page of Project Settings.

#include "NihilistProjectile.h"
#include "Kismet/KismetMathLibrary.h"

void ANihilistProjectile::ApplyHitEffects(FHitResult Hit)
{
    int RandomInt = UKismetMathLibrary::RandomIntegerInRange(0, 100);
    if (RandomInt > 80)
    {
        FVector ActorOrigin;
        FVector ActorBoxExtend;
        AActor* HitActor = Hit.GetActor();
        if (HitActor)
        {
            Hit.GetActor()->GetActorBounds(false, ActorOrigin, ActorBoxExtend);
            FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(ActorOrigin, ActorBoxExtend);
            GetWorld()->SpawnActor<AActor>(WeakPointClass, SpawnLocation, FRotator(0, 0, 0));
        }
    }
}
