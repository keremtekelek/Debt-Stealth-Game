
#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../Debt.h"
#include "BTTask_SetMovementSpeed.generated.h"


UCLASS()
class DEBT_API UBTTask_SetMovementSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	//Getting EMovementSpeed Enum
	UPROPERTY(EditAnywhere)
	EMovementSpeed EnemyMovementType;

	
};




