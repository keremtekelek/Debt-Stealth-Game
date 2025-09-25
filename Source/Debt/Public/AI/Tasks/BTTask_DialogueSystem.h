#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UI/DialogueWidgetCPP.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PlayerControllerCPP.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h" 
#include "Sound/SoundAttenuation.h"
#include "GameFramework/Actor.h"
#include "BTTask_DialogueSystem.generated.h"

UCLASS()
class DEBT_API UBTTask_DialogueSystem : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// VARIABLES!!	

	//** Editable from Outside Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* DialogueVoice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundAttenuation* DialogueSoundAttenuation;

	UPROPERTY(EditAnywhere)
	float DialogueSoundVolume = 1.0f;

	


	//** Normal Variables
	UPROPERTY()
	UDialogueWidgetCPP* Dialogue_Widget;

	UPROPERTY()
	APlayerControllerCPP* PlayerController;

	UPROPERTY()
	float DialogueDuration;


	UPROPERTY()
	FTimerHandle DialogueTimerHandle;

	UPROPERTY()
	AActor* OwnerActor;

	UPROPERTY()
	bool DoOnce = true;

	UPROPERTY()
	UBehaviorTreeComponent* OwnerComponent;


	

	//FUNCTIONS!!!

	UFUNCTION()
	void GetDialogueWidget();

	UFUNCTION()
	void SetUpTheDialogue();

	UFUNCTION()
	void HideSubtitle();
};
