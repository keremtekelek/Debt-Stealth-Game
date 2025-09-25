#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UI/DialogueWidgetCPP.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PlayerControllerCPP.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h" 
#include "Sound/SoundAttenuation.h"
#include "GameFramework/Actor.h"
#include "DataTables/DialogueStruct.h"
#include "Enums/GlobalEnums.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ActorComponent.h"
#include "DialogueSystemCPP.generated.h"

class AEnemyBase;
class AAIC_Enemy;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable)
class DEBT_API UDialogueSystemCPP : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UDialogueSystemCPP();

	//VARIABLES!!!

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DialogueDataTable;

	UPROPERTY()
	FName AboutDialogue;
	
	UPROPERTY()
	FText DialogueText;

	UPROPERTY()
	USoundBase* DialogueVoice;

	UPROPERTY()
	USoundAttenuation* DialogueSoundAttenuation;

	UPROPERTY()
	float DialogueSoundVolume;

	UPROPERTY()
	UDialogueWidgetCPP* Dialogue_Widget;

	UPROPERTY()
	APlayerControllerCPP* PlayerController;

	UPROPERTY()
	float DialogueDuration;

	UPROPERTY()
	FTimerHandle DialogueTimerHandle;

	UPROPERTY()
	AEnemyBase* Enemy;

	UPROPERTY()
	AAIC_Enemy* AI_Controller;

	UPROPERTY()
	FDialogueStruct DialogueStruct;

	UPROPERTY()
	TArray<FDialogueStruct> DialogueRows;

	UPROPERTY()
	FName RowName;

	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	UPROPERTY()
	FBlackboardValueFilter RequiredFilter;

	UPROPERTY()
	bool DoesMatch;

	//ENUMS for Blackboard!!!

	UPROPERTY()
	uint8 Enemy_Situtation;

	UPROPERTY()
	uint8 Enemy_AlarmLevel;

	UPROPERTY()
	uint8 Enemy_HeardReason;

	UPROPERTY()
	uint8 Heard_FootStepMovement_Type;

	UPROPERTY()
	uint8 Enemy_Investigate_Reason;

	UPROPERTY()
	uint8 SuspectedObject;

	UPROPERTY()
	uint8 EventRoom;

	UPROPERTY()
	bool IsPlayerVisible;

	UPROPERTY()
	bool PlayerLostConfirmed;

	UPROPERTY()
	bool PlayerSawConfirmed;

	UPROPERTY()
	bool SawRock;

	UPROPERTY()
	bool IsRockSeenInTheAir;
	

	// Desired Value

	UPROPERTY()
	uint8 Dialogue_Enemy_Situtation;

	UPROPERTY()
	uint8 Dialogue_Enemy_AlarmLevel;

	UPROPERTY()
	uint8 Dialogue_Enemy_HeardReason;

	UPROPERTY()
	uint8 Dialogue_Heard_FootStepMovement_Type;

	UPROPERTY()
	uint8 Dialogue_Enemy_Investigate_Reason;

	UPROPERTY()
	uint8 Dialogue_SuspectedObject;

	UPROPERTY()
	uint8 Dialogue_EventRoom;

	UPROPERTY()
	bool Dialogue_IsPlayerVisible;

	UPROPERTY()
	bool Dialogue_PlayerLostConfirmed;

	UPROPERTY()
	bool Dialogue_PlayerSawConfirmed;

	UPROPERTY()
	bool Dialogue_SawRock;

	UPROPERTY()
	bool Dialogue_IsRockSeenInTheAir;

	
	
	


protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// FUNCTIONS!!!
	UFUNCTION()
	void GetProperties();


	UFUNCTION()
	void PlayDialogue(FName Row_Name);

	UFUNCTION()
	void HideDialogue();

	UFUNCTION()
	void FilterDialogue();

};
