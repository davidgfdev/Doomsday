// Fill out your copyright notice in the Description page of Project Settings.

#include "SetRandomReachablePoint.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <ASCENDENTE/Characters/Sen/Sen.h>
#include <ASCENDENTE/Characters/Enemies/Enemy.h>

EBTNodeResult::Type USetRandomReachablePoint::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{

    FNavLocation ReachableLocation;

    AAIController *Controller = OwnerComp.GetAIOwner();
    AActor *Owner = Controller->GetPawn();

    if (Owner)
    {
        FVector ActorLocation = Owner->GetActorLocation();
        FVector Center = ActorLocation;

        if (isPlayerCenter)
        {
            ASen* SenReference = Cast<AEnemy>(Owner)->GetSenReference();
            if (SenReference)
            {
                FVector SenLocation = Cast<AEnemy>(Owner)->GetSenReference()->GetActorLocation();
                Center = SenLocation;
            }
        }

        UNavigationSystemV1 *NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
        NavSys->GetRandomReachablePointInRadius(Center, Range, ReachableLocation);

        UAIBlueprintHelperLibrary::GetBlackboard(Owner)->SetValueAsVector(GetSelectedBlackboardKey(), ReachableLocation.Location);

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    return EBTNodeResult::Failed;
}