#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "CameraManagerCPP.generated.h"

/**
 * 
 */
UCLASS()
class DEBT_API ACameraManagerCPP : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	
	ACameraManagerCPP();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	//VARIABLES!!!
	UPROPERTY()
	AMainCharacter* MainCharacter;

	UPROPERTY()
	bool IsRockBeingThrown = false;

	//FUNCTIONS!!

	UFUNCTION()
	void ChangeCameraLimitForRockThrowing();

	UFUNCTION()
	void ResetCameraLimit();
};
