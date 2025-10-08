#pragma once
#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Actors/HeadLampCPP.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WearHeadLamp.generated.h"

/**
 * 
 */
UCLASS()
class DEBT_API UBTTask_WearHeadLamp : public UBTTaskNode
{
	GENERATED_BODY()

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY()
	AEnemyBase* Enemy;

	UPROPERTY()
	FName SocketName = "head_lamp_socket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AHeadLampCPP> HeadLamp_Class;

};
