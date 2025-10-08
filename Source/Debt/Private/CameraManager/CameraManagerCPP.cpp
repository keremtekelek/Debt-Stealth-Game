#include "CameraManager/CameraManagerCPP.h"

ACameraManagerCPP::ACameraManagerCPP()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Default Pitch Settings
	ViewPitchMin = -45.f;
	ViewPitchMax = 15.f;

	//Default Yaw Settings
	ViewYawMin = 0.f;
	ViewYawMax = 359.998993f;

	//Default Roll Settings
	ViewRollMin = -80.f;
	ViewRollMax = 80.f;
}


void ACameraManagerCPP::BeginPlay()
{
	Super::BeginPlay();

	AActor* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);

	if (IsValid(PlayerCharacter))
	{
		MainCharacter = Cast<AMainCharacter>(PlayerCharacter);
	}
	
}
	

void ACameraManagerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//** Throwing Rock Situtation
	IsRockBeingThrown = MainCharacter->RockThrowing;

	if (IsRockBeingThrown)
	{
		ChangeCameraLimitForRockThrowing();
	}
	else
	{
		ResetCameraLimit();
	}
	//**

	
}


void ACameraManagerCPP::ChangeCameraLimitForRockThrowing()
{
	float CurrentYaw = MainCharacter->GetActorRotation().Yaw;

	ViewYawMin = CurrentYaw - 60.f;
	ViewYawMax = CurrentYaw + 60.f;
}

void ACameraManagerCPP::ResetCameraLimit()
{
	ViewYawMin = 0.f;
	ViewYawMax = 359.998993f;
}
