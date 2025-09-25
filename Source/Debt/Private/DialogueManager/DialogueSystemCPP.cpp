#include "DialogueManager/DialogueSystemCPP.h"
#include "EnemyBase.h"
#include "AI/AIController/AIC_Enemy.h"




UDialogueSystemCPP::UDialogueSystemCPP()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UDialogueSystemCPP::BeginPlay()
{
	Super::BeginPlay();

	GetProperties();
	
}



void UDialogueSystemCPP::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//FilterDialogue();

}


void UDialogueSystemCPP::GetProperties()
{
	PlayerController = Cast<APlayerControllerCPP>(UGameplayStatics::GetPlayerController(this,0));

	if (PlayerController && PlayerController->DialogueWidgetRef)
	{
		Dialogue_Widget = PlayerController->DialogueWidgetRef;
	}

	
	AActor* OwnerActor = GetOwner();

	if (IsValid(OwnerActor))
	{
		Enemy = Cast<AEnemyBase>(OwnerActor);

		if (IsValid(Enemy))
		{
			AI_Controller = Cast<AAIC_Enemy>(Enemy->GetController());
		}
	}


	PlayerController = Cast<APlayerControllerCPP>(UGameplayStatics::GetPlayerController(this,0));

	if (PlayerController && PlayerController->DialogueWidgetRef)
	{
		Dialogue_Widget = PlayerController->DialogueWidgetRef;
	}
}



void UDialogueSystemCPP::PlayDialogue(FName Row_Name)
{
	
	if (DoesMatch)
	{
		//Play Dialogue
	
		DialogueDuration = DialogueVoice->GetDuration();

		Dialogue_Widget->SetVisibility(ESlateVisibility::Visible);
		Dialogue_Widget->DialogueTextBlock->SetText(DialogueText);

		FVector DialogueLocation = Enemy->GetActorLocation();

		if (DialogueSoundAttenuation)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DialogueVoice, DialogueLocation, DialogueSoundVolume, 1.f, 0.f, DialogueSoundAttenuation);
		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(this, DialogueVoice, DialogueLocation, DialogueSoundVolume, 1.f, 0.f);
		}

		GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UDialogueSystemCPP::HideDialogue, DialogueDuration, false);
	}

}

void UDialogueSystemCPP::HideDialogue()
{
	Dialogue_Widget->SetVisibility(ESlateVisibility::Hidden);
	Dialogue_Widget->DialogueTextBlock->SetText(FText::FromString(TEXT("")));
	GetWorld()->GetTimerManager().ClearTimer(DialogueTimerHandle);
}

void UDialogueSystemCPP::FilterDialogue()
{
	BlackboardComp = AI_Controller->GetBlackboardComponent();

	if (BlackboardComp)
	{
		Enemy_Situtation = BlackboardComp->GetValueAsEnum("EnemySitutation");
		Enemy_Investigate_Reason = BlackboardComp->GetValueAsEnum("Enemy_InvestigateSuspiciousReason");
		Enemy_AlarmLevel = BlackboardComp->GetValueAsEnum("EnemyAlarmLevel");
		Enemy_HeardReason = BlackboardComp->GetValueAsEnum("Enemy_HeardReason");
		Heard_FootStepMovement_Type = BlackboardComp->GetValueAsEnum("HeardFootStepMovementType");
		SuspectedObject = BlackboardComp->GetValueAsEnum("SuspectedObject");
		EventRoom = BlackboardComp->GetValueAsEnum("EventRoom");
		SawRock = BlackboardComp->GetValueAsBool("SawRock");
		IsRockSeenInTheAir = BlackboardComp->GetValueAsBool("IsRockSeenInTheAir");
		PlayerLostConfirmed = BlackboardComp->GetValueAsBool("PlayerLostConfirmed");
		PlayerSawConfirmed = BlackboardComp->GetValueAsBool("PlayerSawConfirmed");
		IsPlayerVisible = BlackboardComp->GetValueAsBool("IsPlayerVisible");
	}

	static const FString Context(TEXT("DialogueSystem"));

	if (DialogueDataTable)
	{
		TArray<FName> RowNames = DialogueDataTable->GetRowNames();

		if (RowNames.Num() > 0)
	{
			
		for (const FName& CurrentRowName : RowNames)
	{
		FDialogueStruct* SelectedRow = DialogueDataTable->FindRow<FDialogueStruct>(CurrentRowName, Context);
		if (!SelectedRow) continue;

		RequiredFilter = SelectedRow->RequiredStates;
			
		DialogueText=SelectedRow->DialogueText;
		DialogueVoice = SelectedRow->DialogueVoice;
		DialogueSoundAttenuation = SelectedRow->DialogueSoundAttenuation;
		DialogueSoundVolume = SelectedRow->DialogueSoundVolume;

		Dialogue_Enemy_Situtation = static_cast<uint8>(RequiredFilter.Enemy_Situation);
		Dialogue_Enemy_Investigate_Reason = static_cast<uint8>(RequiredFilter.Enemy_Investigate_Reason);
		Dialogue_Enemy_AlarmLevel = static_cast<uint8>(RequiredFilter.Enemy_AlarmLevel);
		Dialogue_Enemy_HeardReason = static_cast<uint8>(RequiredFilter.Enemy_HeardReason);
		Dialogue_Heard_FootStepMovement_Type = static_cast<uint8>(RequiredFilter.Heard_FootStepMovement_Types);
		Dialogue_SuspectedObject = static_cast<uint8>(RequiredFilter.SuspectedObjects);
		Dialogue_EventRoom = static_cast<uint8>(RequiredFilter.EventRooms);
		Dialogue_SawRock = static_cast<uint8>(RequiredFilter.SawRock);
		Dialogue_IsRockSeenInTheAir = static_cast<uint8>(RequiredFilter.RockSeenInTheAir);
		Dialogue_PlayerLostConfirmed = static_cast<uint8>(RequiredFilter.PlayerLostConfirmed);
		Dialogue_PlayerSawConfirmed = static_cast<uint8>(RequiredFilter.PlayerSawConfirmed);
		Dialogue_IsPlayerVisible = static_cast<uint8>(RequiredFilter.IsPlayerVisible);
		
		bool RowMatches = 
		Dialogue_Enemy_Situtation==Enemy_Situtation &&
		Dialogue_Enemy_AlarmLevel==Enemy_AlarmLevel &&
		Dialogue_Enemy_Investigate_Reason==Enemy_Investigate_Reason &&
		Dialogue_Enemy_HeardReason==Enemy_HeardReason &&
		Dialogue_Heard_FootStepMovement_Type==Heard_FootStepMovement_Type &&
		Dialogue_SuspectedObject==SuspectedObject &&
		Dialogue_EventRoom==EventRoom &&
		Dialogue_SawRock==SawRock &&
		Dialogue_IsRockSeenInTheAir==IsRockSeenInTheAir &&
		Dialogue_PlayerLostConfirmed==PlayerLostConfirmed &&
		Dialogue_PlayerSawConfirmed==PlayerSawConfirmed &&
		Dialogue_IsPlayerVisible==IsPlayerVisible;

		if (RowMatches)
		{
			DoesMatch=true;
			break;
		}
		else
		{
			DoesMatch=false;
		}
		
	}
	}
	
	}

}


