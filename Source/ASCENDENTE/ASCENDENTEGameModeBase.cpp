// Fill out your copyright notice in the Description page of Project Settings.

#include "ASCENDENTEGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AASCENDENTEGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    StartGame();
    MarkEnemies();
}

void AASCENDENTEGameModeBase::ActorDied(AActor *DeadActor)
{
    DeadActor->Destroy();
}

void AASCENDENTEGameModeBase::MarkEnemies()
{
    int EnemiesMarked = 0;
    AActor *Sen = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    TArray<AActor *> EnemiesInRange;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
    TArray<AActor *> ActorsToIgnore;
    ActorsToIgnore.Add(Sen);

    UKismetSystemLibrary::SphereOverlapActors(GetWorld(),
                                              Sen->GetActorLocation(),
                                              1000,
                                              ObjectTypes,
                                              AActor::StaticClass(),
                                              ActorsToIgnore,
                                              EnemiesInRange);

    if (EnemiesInRange.Num() > 0)
    {
        DrawDebugSphere(GetWorld(), Sen->GetActorLocation(), 1000, 12, FColor::Purple, false, 2.f);

        for (int i = 0; i < EnemiesInRange.Num(); i++)
        {
            AActor *Enemy = Cast<AActor>(EnemiesInRange[i]);
            int RandomInt = UKismetMathLibrary::RandomIntegerInRange(0, 100);
            if (RandomInt > 65)
            {
                UE_LOG(LogTemp, Display, TEXT("Enemigo marcado"));
                EnemiesMarked += 1;
                DrawDebugSphere(GetWorld(), Enemy->GetActorLocation(), 200, 12, FColor::Yellow, false, 60);
            }
        }

        if (EnemiesMarked == 0)
        {
            MarkEnemies();
        }
    }
}
