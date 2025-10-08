#include "AI/Tasks/BTTask_WearHeadLamp.h"

#include "AIController.h"

EBTNodeResult::Type UBTTask_WearHeadLamp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	if (IsValid(ControlledPawn) && HeadLamp_Class)
	{
		Enemy = Cast<AEnemyBase>(ControlledPawn);

		

		FVector SpawnLocation;
		FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
		FActorSpawnParameters SpawnParams;
		
		SpawnLocation = Enemy->GetMesh()->GetSocketLocation(SocketName);
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;
		
		AHeadLampCPP* SpawnedActor = GetWorld()->SpawnActor<AHeadLampCPP>(HeadLamp_Class,SpawnLocation,SpawnRotation,SpawnParams);

		if (IsValid(SpawnedActor))
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::KeepWorld,true);
			SpawnedActor->AttachToComponent(Enemy->GetMesh(),AttachmentRules, SocketName);

			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
		
	return EBTNodeResult::Succeeded;
		
	}
	else
	{
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Succeeded;
}
