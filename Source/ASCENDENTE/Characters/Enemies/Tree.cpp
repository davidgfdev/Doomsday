// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "../Source/ASCENDENTE/ASCENDENTEGameModeBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Source/ASCENDENTE/Characters/Sen/Sen.h"
#include "Tree.h"

void ATree::HandleDeath()
{
	AASCENDENTEGameModeBase* GameMode = Cast<AASCENDENTEGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	EndGame();
}

void ATree::LookAtPlayer() 
{
    if (SenReference)
    {
        FVector PlayerLocation = SenReference->GetActorLocation();
        FVector EnemyLocation = GetActorLocation();

        FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(EnemyLocation, PlayerLocation);
        FRotator FixedRotator = GetActorRotation();
        FixedRotator.Yaw = LookAtRotation.Yaw;

        SetActorRotation(FQuat::MakeFromRotator(FixedRotator));
    }
}

