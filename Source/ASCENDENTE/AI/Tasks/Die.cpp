// Fill out your copyright notice in the Description page of Project Settings.

#include "Die.h"
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

EBTNodeResult::Type UDie::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	OwnerComp.StopTree();
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Failed;
}

