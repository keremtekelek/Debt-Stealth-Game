#include "AI/Tasks/BTTask_DialogueSystem.h"

EBTNodeResult::Type UBTTask_DialogueSystem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerActor = OwnerComp.GetOwner();
	OwnerComponent = &OwnerComp;
	GetDialogueWidget();

	
	if (DoOnce)
	{
		SetUpTheDialogue();
		DoOnce = false;
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Succeeded;
	
}


void UBTTask_DialogueSystem::GetDialogueWidget()
{
	PlayerController = Cast<APlayerControllerCPP>(UGameplayStatics::GetPlayerController(this,0));

	if (PlayerController && PlayerController->DialogueWidgetRef)
	{
		Dialogue_Widget = PlayerController->DialogueWidgetRef;
	}

}

void UBTTask_DialogueSystem::SetUpTheDialogue()
{
	if (DialogueVoice)
	{
		DialogueDuration = DialogueVoice->GetDuration();
		
		Dialogue_Widget->SetVisibility(ESlateVisibility::Visible);
		Dialogue_Widget->DialogueTextBlock->SetText(DialogueText);

		FVector DialogueLocation = OwnerActor->GetActorLocation();

		if (DialogueSoundAttenuation)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DialogueVoice, DialogueLocation, DialogueSoundVolume, 1.f, 0.f, DialogueSoundAttenuation);
		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(this, DialogueVoice, DialogueLocation, DialogueSoundVolume, 1.f, 0.f);
		}


		

		
		  GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UBTTask_DialogueSystem::HideSubtitle, DialogueDuration, false);
		 
	}
}

void UBTTask_DialogueSystem::HideSubtitle()
{
	Dialogue_Widget->SetVisibility(ESlateVisibility::Hidden);
	Dialogue_Widget->DialogueTextBlock->SetText(FText::FromString(TEXT("")));
	GetWorld()->GetTimerManager().ClearTimer(DialogueTimerHandle);

	if (OwnerComponent)
	{
		FinishLatentTask(*OwnerComponent, EBTNodeResult::Succeeded);
	}
	
}