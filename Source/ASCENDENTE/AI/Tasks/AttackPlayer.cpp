// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackPlayer.h"
#include "AIController.h"
#include "..\Source\ASCENDENTE\Characters\Enemies\Enemy.h"

EBTNodeResult::Type UAttackPlayer::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    AAIController *Controller = OwnerComp.GetAIOwner();
    AActor *Owner = Controller->GetPawn();

    if (Owner)
    {
        Cast<AEnemy>(Owner)->Attack();

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    return EBTNodeResult::Failed;
}