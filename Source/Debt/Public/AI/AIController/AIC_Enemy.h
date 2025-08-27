
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
#include "TimerManager.h" 
#include "EngineUtils.h"
#include "Enums/GlobalEnums.h"
#include "EnemyBase.h"
#include "PlayerController/PlayerControllerCPP.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Containers/UnrealString.h"
#include "GameFramework/Character.h"
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


	//FUNCTIONS!!


	//Tick Function
	virtual void Tick(float DeltaTime) override;

private:
	//VARIABLES!!!

	// Suspicious Meter Values
	UPROPERTY()
	float SuspiciousLevel;

	UPROPERTY()
	UWidgetComponent* SuspiciousMeter_WidgetComponent;

	UPROPERTY()
	UUserWidget* SuspiciousMeter_Widget;

public:

	//VARIABLES!!!

	
	UPROPERTY(VisibleAnywhere)
	AEnemyBase* Enemy;
	




	// Timer Variables
	UPROPERTY(VisibleAnywhere)
	FTimerHandle SightLostTimerHandle;

	UPROPERTY(VisibleAnywhere)
	FTimerHandle GetEnemyAndWidgetTimerHandle;

	//PlayerCharacter Reference
	UPROPERTY(VisibleAnywhere)
	ACharacter* PlayerCharacter;

	//ENUMS for AI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemy_SuspiciousReason Eenemy_SuspiciousReason;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemySitutation EenemySitutation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemy_AlarmLevel Eenemy_AlarmLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemy_HeardReason Eenemy_HeardReason;


	// Sense ID's
	FAISenseID SenseSightID;
	FAISenseID SenseHearID;
	FAISenseID SensePredictionID;






	//FUNCTIONS




	//BeginPlay Function
	virtual void BeginPlay() override;

	//OnTargetPerceptionUpdated Function is defined.
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	
	// Suspicious Meter Functions

	UFUNCTION()
	void HandleSuspicionMeter(float DeltaTime);

	UFUNCTION()
	void ResetSuspicionMeter();
	




	// Timer Functions
	UFUNCTION()
	void OnSightLostConfirmed();

	UFUNCTION()
	void GetEnemyAndWidget();


	//Sight Sense Functions that handles the EnemySeenDuration for the detection bar and realism
	UFUNCTION()
	void OnSightSeeConfirmedLong();

	UFUNCTION()
	void OnSightSeeConfirmShort();




	//Getting Enemy Situtations by Functions


	UFUNCTION(BlueprintCallable, Category = "AI")
	EEnemySitutation GetEnemySitutation() const;

	UFUNCTION(BlueprintCallable, Category = "AI")
	EEnemy_AlarmLevel GetEnemyAlarmLevel() const;
	

	UFUNCTION(BlueprintCallable, Category = "AI")
	EEnemy_SuspiciousReason GetEnemySuspiciousReason() const;

	UFUNCTION(BlueprintCallable, Category = "AI")
	EEnemy_HeardReason GetEnemyHeardReason() const;

	
	

	
	//Setting Enemy Situtations by Functions

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetEnemySitutationAs(EEnemySitutation NewSitutation);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetEnemyAlarmLevelAs(EEnemy_AlarmLevel NewAlarmLevel);


	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetEnemyInvestigateReasonAs(EEnemy_SuspiciousReason NewSuspiciousReason);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetEnemyHeardReasonAs(EEnemy_HeardReason NewHeardReason);



	// Defining AI Communication Functions

	UFUNCTION()
	void WarnOtherAIs(EEnemySitutation Situtation, EEnemy_AlarmLevel AlarmLevel, FVector AlarmLocation, EEnemy_SuspiciousReason Reason);


	UFUNCTION()
	void ReceiveWarnFromOtherAI(EEnemySitutation Situtation, EEnemy_AlarmLevel AlarmLevel, FVector AlarmLocation, EEnemy_SuspiciousReason Reason);
	
};
