
#include "AI/Decorators/BTD_HasPatrolRoute.h"

bool UBTD_HasPatrolRoute::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    //Getting AI controller from owner and checking for validitation
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return false;
    }

    //Getting ControlledPawn from AIController and checking for validitation
    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn)
    {
        return false;
    }

    // If controlled pawn has the PatrolRouteProvider interface, if statement going to do valididation of PatrolRoute.
    if (ControlledPawn->GetClass()->ImplementsInterface(UInterface_EnemyAI::StaticClass()))
    {
        APatrolRoute* PatrolRoute = IInterface_EnemyAI::Execute_GetPatrolRoute(ControlledPawn);

        if (IsValid(PatrolRoute))
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }

}