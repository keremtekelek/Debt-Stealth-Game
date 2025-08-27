#include "AI/Tasks/BTTask_SetMovementSpeed.h"
#include "AI/AIController/AIC_Enemy.h"
#include "Interfaces/Interface_EnemyAI.h"


EBTNodeResult::Type UBTTask_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
       
        return EBTNodeResult::Failed;
    }


    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn)
    {
        
        return EBTNodeResult::Failed;
    }

    //If controlled pawn has the PatrolRouteProvider interface, going to execute SetMovementSpeed function from interface and returns Succeeded
    if (ControlledPawn->GetClass()->ImplementsInterface(UInterface_EnemyAI::StaticClass()))
    {
      
        float b = IInterface_EnemyAI::Execute_SetMovementSpeed(ControlledPawn, EnemyMovementType);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
