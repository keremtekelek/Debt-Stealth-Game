
#include "AI/Tasks/BTTask_MovingOnPatrol.h"
#include "Interfaces/Interface_EnemyAI.h"

EBTNodeResult::Type UBTTask_MovingOnPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AIController = OwnerComp.GetAIOwner();
    if (!AIController) {
        return EBTNodeResult::Failed;
    }

    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn) {
        return EBTNodeResult::Failed;
    }

    if (ControlledPawn->GetClass()->ImplementsInterface(UInterface_EnemyAI::StaticClass()))
    {
        APatrolRoute* PatrolRoute = IInterface_EnemyAI::Execute_GetPatrolRoute(ControlledPawn);

        if (IsValid(PatrolRoute))
        {
            FVector SplinePointLocation = PatrolRoute->GetSplinePointAsWorldPosition();


            UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
            if (BlackboardComp)
            {
                BlackboardComp->SetValueAsVector(FName("PatrolSplineLocation"), SplinePointLocation);

                PatrolRoute->IncrementPatrolRoute();
                return EBTNodeResult::Succeeded;
            }
            else
            {
                return EBTNodeResult::Failed;
            }
        }
        else
        {
            return EBTNodeResult::Failed;
        }
    }

    return EBTNodeResult::Failed;
}
