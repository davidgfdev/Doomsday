// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "../Source/ASCENDENTE/ASCENDENTEGameModeBase.h"
#include "Tree.h"

void ATree::HandleDeath()
{
	AASCENDENTEGameModeBase* GameMode = Cast<AASCENDENTEGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	EndGame();
}

