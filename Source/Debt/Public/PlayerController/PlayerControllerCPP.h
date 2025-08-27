// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Enums/GlobalEnums.h"
#include "PlayerControllerCPP.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct F_DetectionMeterValues
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float SeenDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	DetectionMeter_Reason DetectionMeter_reason;

	
	UPROPERTY(BlueprintReadOnly)
	EEnemy_AlarmLevel AlarmLevel;

	UPROPERTY(BlueprintReadOnly)
	EEnemySitutation EnemySitutation;
};





UCLASS()
class DEBT_API APlayerControllerCPP : public APlayerController
{
	GENERATED_BODY()
	
public:

	//UPROPERTY(EditDefaultsOnly, Category="UI")
	//TSubclassOf<class UUserWidget> WidgetReferance;

	//UPROPERTY()
	//class UUserWidget* createdWidget;


	

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DetectionMeterStarted(DetectionMeter_Reason Reason);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DetectionMeterStopped();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateDetectionMeterValues(float SeenDuration, EEnemySitutation Situtation,EEnemy_AlarmLevel Alarm_Level);



	

	
	



	virtual void BeginPlay() override;
};



