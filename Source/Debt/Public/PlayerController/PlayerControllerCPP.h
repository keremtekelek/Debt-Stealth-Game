// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UI/DialogueWidgetCPP.h"
#include "CameraManager/CameraManagerCPP.h"
#include "PlayerControllerCPP.generated.h"

/**
 * 
 */

UCLASS()
class DEBT_API APlayerControllerCPP : public APlayerController
{
	GENERATED_BODY()

	APlayerControllerCPP();
	
public:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UDialogueWidgetCPP* DialogueWidgetRef;

	UPROPERTY()
	TSubclassOf<UDialogueWidgetCPP> DialogueWidgetClass;

	UPROPERTY()
	ACameraManagerCPP* Player_CameraManager;
};



