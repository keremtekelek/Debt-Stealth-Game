// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI/AIController/AIC_Enemy.h"
#include "Navigation/PathFollowingComponent.h"
#include "BTTask_MovingOnPatrol.generated.h"

/**
 * 
 */
UCLASS()
class DEBT_API UBTTask_MovingOnPatrol : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	AAIController* AIController;
};
