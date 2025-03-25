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
        Cast<AEnemy>(DeadActor)->HandleDeath();
    }
}
