#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/Interface_Interaction.h"
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

	//**VARIABLES!!!**//

	// Main Character Variables
	UPROPERTY()
	AMainCharacter* MainCharacter;

	UPROPERTY()
	UCameraComponent* Main_Camera;

	UPROPERTY()
	USpringArmComponent* Main_SpringArm;

	UPROPERTY()
	bool IsRockBeingThrown = false;

	UPROPERTY()
	bool IsCharacterCrouching;

	// Spring Arm Variables
	
	UPROPERTY()
	float SpringArm_TargetLength = 130.f;

	UPROPERTY()
	FVector SpringArm_SocketOffset = FVector(0.f,50.f,25.f);

	UPROPERTY()
	FVector SpringArm_Location = FVector(0.f,0.f,48.5f);

	// Camera Variables

	UPROPERTY()
	FRotator Camera_Rotation = FRotator(0.f,-5.f,0.f);


	
	//FUNCTIONS!!

	UFUNCTION()
	void ChangeCameraLimitForRockThrowing();

	UFUNCTION()
	void ResetCameraLimit();

	UFUNCTION()
	void ChangeCameraPositionOnCrouching();

	UFUNCTION()
	void ResetCameraPosition();
};
