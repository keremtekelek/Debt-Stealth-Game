// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI/AIController/AIC_Enemy.h"
#include "BTTask_SetEnemyProperties.generated.h"

/**
 * 
 */
UCLASS()
class DEBT_API UBTTask_SetEnemyProperties : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTask_SetEnemyProperties();
public:

	//Defining Variables
	UPROPERTY(EditAnywhere, Category = "Desired Enemy Values", meta = (InlineEditConditionToggle))
	bool bShouldSetEnemySitutation;

	UPROPERTY(EditAnywhere, Category = "Desired Enemy Values", meta = (InlineEditConditionToggle))
	bool bShouldSetEnemyAlarmLevel;

	UPROPERTY(EditAnywhere, Category = "Desired Enemy Values", meta = (InlineEditConditionToggle))
	bool bShouldSetEnemyInvestigationReason;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Desired Enemy Values", meta = (EditCondition = "bShouldSetEnemySitutation"))
	EEnemySitutation Desired_EnemySitutation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Desired Enemy Values", meta = (EditCondition = "bShouldSetEnemyAlarmLevel"))
	EEnemy_AlarmLevel Desired_EnemyAlarmLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Desired Enemy Values", meta = (EditCondition = "bShouldSetEnemyInvestigationReason"))
	EEnemy_SuspiciousReason Desired_EnemyInvestigateReason;

	





	

	






	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
