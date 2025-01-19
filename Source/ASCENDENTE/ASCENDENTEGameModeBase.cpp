// Fill out your copyright notice in the Description page of Project Settings.

#include "ASCENDENTEGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "..\Source\ASCENDENTE\Characters\Enemies\Enemy.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"

void AASCENDENTEGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    StartGame();

    FTimerHandle MarkingTimerHandler;
    GetWorldTimerManager().SetTimer(MarkingTimerHandler, this, &AASCENDENTEGameModeBase::MarkEnemies, MarkingSeconds, true);
}

void AASCENDENTEGameModeBase::ActorDied(AActor *DeadActor)
{
    if (DeadActor->IsA(ASen::StaticClass()))
    {
        Cast<ASen>(DeadActor)->HandleDeath();
    }
    else
    {
        ASen *Sen = Cast<ASen>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
        Sen->AddAscensionKills();
        Cast<AEnemy>(DeadActor)->HandleDeath();
    }
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
                                              800,
                                              ObjectTypes,
                                              AEnemy::StaticClass(),
                                              ActorsToIgnore,
                                              EnemiesInRange);

    if (EnemiesInRange.Num() > 0)
    {
        DrawDebugSphere(GetWorld(), Sen->GetActorLocation(), 800, 12, FColor::Purple, false, 2.f);

        for (int i = 0; i < EnemiesInRange.Num(); i++)
        {
            AEnemy *Enemy = Cast<AEnemy>(EnemiesInRange[i]);
            int RandomInt = UKismetMathLibrary::RandomIntegerInRange(0, 100);
            if (RandomInt > 65 && !Enemy->bIsMarkedForAbsolution)
            {
                UE_LOG(LogTemp, Display, TEXT("Enemigo marcado"));
                EnemiesMarked += 1;
                Enemy->MarkForAbsolution();
            }
        }
    }
}
