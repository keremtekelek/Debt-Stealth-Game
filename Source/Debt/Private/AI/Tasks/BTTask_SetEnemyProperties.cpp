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

	


	/*
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	bool IsPlayerVisible = BlackboardComponent->GetValueAsBool(FName("IsPlayerVisible"));
	if (!BlackboardComponent) return EBTNodeResult::Failed;
	*/


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







/*
	* if (bShouldSetEnemySitutation == true)
		{
			switch (Desired_EnemySitutation)
			{
			case EEnemySitutation::Patrol:
				NPC_Controller->SetEnemySitutationAs(EEnemySitutation::Patrol);

				break;
			case EEnemySitutation::Investigate:
				NPC_Controller->SetEnemySitutationAs(EEnemySitutation::Investigate);
				break;
			case EEnemySitutation::Alarm:
				NPC_Controller->SetEnemySitutationAs(EEnemySitutation::Alarm);;
				break;
			case EEnemySitutation::LifeCycle:
				NPC_Controller->SetEnemySitutationAs(EEnemySitutation::LifeCycle);;
				break;
			case EEnemySitutation::None:
				NPC_Controller->SetEnemySitutationAs(EEnemySitutation::None);;
				break;
			default:
				break;
			}

		}


		if (bShouldSetEnemyAlarmLevel == true)
		{
			switch (Desired_EnemyAlarmLevel)
			{
			case EEnemy_AlarmLevel::HugeAlarm:
				NPC_Controller->SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::HugeAlarm);

				break;
			case EEnemy_AlarmLevel::BigAlarm:
				NPC_Controller->SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::BigAlarm);

				break;
			case EEnemy_AlarmLevel::MiddleAlarm:
				NPC_Controller->SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::MiddleAlarm);;

				break;
			case EEnemy_AlarmLevel::SmallAlarm:
				NPC_Controller->SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::SmallAlarm);;

				break;
			case EEnemy_AlarmLevel::None:
				NPC_Controller->SetEnemyAlarmLevelAs(EEnemy_AlarmLevel::None);;

				break;
			default:
				break;
			}

		}


		if (bShouldSetEnemyInvestigationReason == true)
		{
			switch (Desired_EnemyInvestigateReason)
			{
			case EEnemy_SuspiciousReason::Saw:
				NPC_Controller->SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Saw);
				break;
			case EEnemy_SuspiciousReason::Damage:
				NPC_Controller->SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Damage);
				break;
			case EEnemy_SuspiciousReason::Heard:
				NPC_Controller->SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Heard);;
				break;
			case EEnemy_SuspiciousReason::Smell:
				NPC_Controller->SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Smell);;
				break;
			case EEnemy_SuspiciousReason::Touch:
				NPC_Controller->SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::Touch);;
				break;

			case EEnemy_SuspiciousReason::None:
				NPC_Controller->SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason::None);;
				break;

			default:
				break;
			}

		}

	return EBTNodeResult::Succeeded;
}

	*/











