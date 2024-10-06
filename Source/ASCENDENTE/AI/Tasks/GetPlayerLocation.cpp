// Fill out your copyright notice in the Description page of Project Settings.

#include "GetPlayerLocation.h"
#include "..\Source\ASCENDENTE\Characters\Enemies\Enemy.h"
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UGetPlayerLocation::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    AAIController *Controller = OwnerComp.GetAIOwner();
    AActor *Owner = Controller->GetPawn();

    if (Owner)
    {
        ASen *SenReference = Cast<AEnemy>(Owner)->GetSenReference();
        if (SenReference)
        {
            FVector SenLocation = Cast<AEnemy>(Owner)->GetSenReference()->GetActorLocation();
            UAIBlueprintHelperLibrary::GetBlackboard(Owner)->SetValueAsVector(GetSelectedBlackboardKey(), SenLocation);

            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            return EBTNodeResult::Succeeded;
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT("Can't get Sen Reference"));
        }
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    return EBTNodeResult::Failed;
}
