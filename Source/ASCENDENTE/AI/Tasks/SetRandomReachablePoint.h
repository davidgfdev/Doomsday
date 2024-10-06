// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SetRandomReachablePoint.generated.h"

/**
 *
 */
UCLASS()
class ASCENDENTE_API USetRandomReachablePoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory);

private:
	UPROPERTY(EditAnywhere, Category = "Distance")
	float Range = 1500;
};
