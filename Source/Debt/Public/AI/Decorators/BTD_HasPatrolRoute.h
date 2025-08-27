

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "AIController.h"
#include "Interfaces/Interface_EnemyAI.h"
#include "BTD_HasPatrolRoute.generated.h"

/**
 * 
 */
UCLASS()
class DEBT_API UBTD_HasPatrolRoute : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	//"CalculateRawConditionValue" is nearly to equal "PerformConditionCheckAI" on the Blueprints
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
