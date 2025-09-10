
#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Prediction.h"
#include "Perception/AISense_Prediction.h"
#include "NavigationSystem.h"
#include "TimerManager.h" 
#include "EngineUtils.h"
#include "Engine/Light.h"
#include "Enums/GlobalEnums.h"
#include "EnemyBase.h"
#include "PlayerController/PlayerControllerCPP.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Containers/UnrealString.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Actors/Interactables/BookCPP.h"
#include "Actors/Interactables/ComputerCPP.h"
#include "Actors/Interactables/LightSwitchCPP.h"
#include "Actors/Interactables/CoffeeMachineCPP.h"
#include "UI/SuspiciousMeterCPP.h"
#include "AIC_Enemy.generated.h"


UCLASS()
class DEBT_API AAIC_Enemy : public AAIController
{
	GENERATED_BODY()

public:

	virtual void OnPossess(APawn* InPawn) override;
	AAIC_Enemy();


protected:

	// VARIABLES!!!

	

	//Creating BehaviourTree variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BT_EnemyAI_Base;

	//Creating BehaviourTree variable
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UBlackboardComponent* BlackboardComp;

	//Creating AI Perception Component variable
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComp;

	//Creating Sense Sight Config variable
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Sight* SightConfig;

	// Creating Sense Hearing Config variable
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Hearing* HearingConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Prediction* PredictionConfig;

	UPROPERTY(VisibleAnywhere)
	bool CanTick = false;



	//FUNCTIONS!!



	
	virtual void Tick(float DeltaTime) override;

private:

	//VARIABLES!!!



	// Suspicioun Meter Values
	
	UPROPERTY()
	UWidgetComponent* SuspiciousMeter_WidgetComponent;

	UPROPERTY()
	USuspiciousMeterCPP* SuspiciousMeter_Widget;
	
public:

	//VARIABLES!!!

	/*
	UPROPERTY(VisibleAnywhere)
	TArray<ABookCPP*> BooksArray;
	*/
	
	
	UPROPERTY(VisibleAnywhere)
	AEnemyBase* Enemy;
	
	// Timer Variables
	UPROPERTY(VisibleAnywhere)
	FTimerHandle PlayerSawOrLostTimerHandle;

	UPROPERTY(VisibleAnywhere)
	FTimerHandle GetEnemyAndWidgetTimerHandle;

	UPROPERTY(VisibleAnywhere)
	FTimerHandle DelayHandler;

	UPROPERTY(VisibleAnywhere)
	FTimerHandle GetRoomNameHandler;

	FTimerDelegate PlayerSawOrLostTimerDelegate;

	UPROPERTY(VisibleAnywhere)
	ACharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemy_SuspiciousReason Eenemy_SuspiciousReason;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemySitutation EenemySitutation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemy_AlarmLevel Eenemy_AlarmLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemy_HeardReason Eenemy_HeardReason;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESuspiciousMeterType TypeOfSuspicion;


	// Sense ID's
	FAISenseID SenseSightID;
	FAISenseID SenseHearID;
	FAISenseID SensePredictionID;

	

	

	//FUNCTIONS!!!



	
	virtual void BeginPlay() override;

	
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	// Suspicious Meter Functions

	UFUNCTION()
	void HandleSuspiciousMeter(float DeltaTime);

	UFUNCTION()
	void ResetSuspiciousMeter();

	UFUNCTION()
	void OpenOrCloseWidget(FString TypeQuestionOrExclamation, FString TypeOpenOrClose);
	

	// Timer Functions
	UFUNCTION()
	void PlayerSawOrLostConfirmed(FString TypeSawOrLost,bool ChangeItTrueOrFalse);

	UFUNCTION()
	void GetEnemyAndWidget();

	UFUNCTION()
	void DelayHandlerFunction();


	UFUNCTION(BlueprintCallable, Category = "AI")
	EEnemySitutation GetEnemySitutation() const;

	UFUNCTION(BlueprintCallable, Category = "AI")
	EEnemy_AlarmLevel GetEnemyAlarmLevel() const;
	

	UFUNCTION(BlueprintCallable, Category = "AI")
	EEnemy_SuspiciousReason GetEnemySuspiciousReason() const;

	UFUNCTION(BlueprintCallable, Category = "AI")
	EEnemy_HeardReason GetEnemyHeardReason() const;

	UFUNCTION(BlueprintCallable, Category = "AI")
	EEventRoom GetEventRoom() const;

	UFUNCTION(BlueprintCallable, Category = "AI")
	ESuspectedObject GetSuspectedObject() const;

	//Setting Enemy Blackboard Values by Functions

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetEnemySitutationAs(EEnemySitutation NewSitutation);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetEnemyAlarmLevelAs(EEnemy_AlarmLevel NewAlarmLevel);


	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason NewSuspiciousReason);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetEnemyHeardReasonAs(EEnemy_HeardReason NewHeardReason);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetEventRoom(EEventRoom NewEventRoom);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetSuspectedObject(ESuspectedObject NewSuspectedObject);
	

	
	// Defining AI Communication Functions

	UFUNCTION()
	void WarnOtherAIs(EEnemySitutation Situtation, EEnemy_AlarmLevel AlarmLevel, FVector AlarmLocation, EEnemy_SuspiciousReason Reason);

	UFUNCTION()
	void ReceiveWarnFromOtherAI(EEnemySitutation Situtation, EEnemy_AlarmLevel AlarmLevel, FVector AlarmLocation, EEnemy_SuspiciousReason Reason);

	//

	

	
};
