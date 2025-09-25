#include "AI/Tasks/BTTask_SetEnemyProperties.h"
#include "Kismet/GameplayStatics.h"




UBTTask_SetEnemyProperties::UBTTask_SetEnemyProperties()
{
	NodeName = "Set Enemy Properties";

	bShouldSetEnemySitutation = false;
	bShouldSetEnemyAlarmLevel = false;
	bShouldSetEnemyInvestigationReason = false;
	
}

EBTNodeResult::Type UBTTask_SetEnemyProperties::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	//Getting AIController
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	//And casting to the our default AIController
	AAIC_Enemy* NPC_Controller = Cast<AAIC_Enemy>(AIController);
	if (!NPC_Controller) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;
		
	

	if (bShouldSetEnemySitutation == true)
	{
		BlackboardComp->SetValueAsEnum(FName("EnemySitutation"), static_cast<uint8>(Desired_EnemySitutation));
	}


	if (bShouldSetEnemyAlarmLevel == true)
	{
		BlackboardComp->SetValueAsEnum(FName("EnemyAlarmLevel"), static_cast<uint8>(Desired_EnemyAlarmLevel));
	}


	if (bShouldSetEnemyInvestigationReason == true)
	{
		BlackboardComp->SetValueAsEnum(FName("Enemy_InvestigateSuspiciousReason"), static_cast<uint8>(Desired_EnemyInvestigateReason));
	}

	return EBTNodeResult::Succeeded;
}










