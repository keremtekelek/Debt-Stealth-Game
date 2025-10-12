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

	if (IsValid(MainCharacter))
	{
		//Get Components and Variables from Main Character
		
		Main_Camera = MainCharacter->PlayerCamera;
		Main_SpringArm = MainCharacter->Camera_SpringArm;
	}

	if (Main_SpringArm && Main_Camera)
	{
		//**Spring Arm Settings
		Main_SpringArm->TargetArmLength = SpringArm_TargetLength;
		Main_SpringArm->SocketOffset = SpringArm_SocketOffset;
		Main_SpringArm->SetRelativeLocation(SpringArm_Location);
		Main_SpringArm->bInheritRoll = false;
		
		
		Main_SpringArm->bEnableCameraLag = true;
		Main_SpringArm->bEnableCameraRotationLag = true;
		Main_SpringArm->CameraLagSpeed = 12.f;
		Main_SpringArm->CameraRotationLagSpeed = 12.f;
		

		//**Camera Settings

		Main_Camera->SetRelativeRotation(Camera_Rotation);
		
	}
}
	

void ACameraManagerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IsRockBeingThrown = MainCharacter->RockThrowing;
	IsCharacterCrouching = MainCharacter->bIsCrouchingg;
	
	//** Throwing Rock Situtation
	
	if (IsRockBeingThrown)
	{
		ChangeCameraLimitForRockThrowing();
	}
	else
	{
		ResetCameraLimit();
	}
	//**

	if (IsCharacterCrouching)
	{
		ChangeCameraPositionOnCrouching();
	}
	else
	{
		ResetCameraPosition();
	}
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

void ACameraManagerCPP::ChangeCameraPositionOnCrouching()
{
	FVector SpringArm_SocketOffset_Crouch = FVector(0.f,0.f,10.f);
	FVector SpringArm_Location_Crouch = FVector(0.f,0.f,30.f);
	float SpringArm_TargetLength_Crouch = 270.f;

	float Current_TargetLength = Main_SpringArm->TargetArmLength;
	FVector Current_TargetLocation = Main_SpringArm->GetRelativeLocation();
	FVector Current_SocketOffset = Main_SpringArm->SocketOffset;
	
	Main_SpringArm->TargetArmLength = FMath::FInterpTo(Current_TargetLength,SpringArm_TargetLength_Crouch,GetWorld()->GetDeltaSeconds(),2.f);

	Main_SpringArm->SetRelativeLocation((FMath::VInterpTo(Current_TargetLocation,SpringArm_Location_Crouch,GetWorld()->GetDeltaSeconds(),2.f)));

	Main_SpringArm->SocketOffset = (FMath::VInterpTo(Current_SocketOffset,SpringArm_SocketOffset_Crouch,GetWorld()->GetDeltaSeconds(),2.f));
	
}

void ACameraManagerCPP::ResetCameraPosition()
{
	
	float Current_TargetArmLength = Main_SpringArm->TargetArmLength;
	FVector Current_TargetLocation = Main_SpringArm->GetRelativeLocation();
	FVector Current_SocketOffset = Main_SpringArm->SocketOffset;

	Main_SpringArm->TargetArmLength = FMath::FInterpTo(Current_TargetArmLength,SpringArm_TargetLength,GetWorld()->GetDeltaSeconds(),2.f);

	Main_SpringArm->SetRelativeLocation((FMath::VInterpTo(Current_TargetLocation,SpringArm_Location,GetWorld()->GetDeltaSeconds(),2.f)));

	Main_SpringArm->SocketOffset = (FMath::VInterpTo(Current_SocketOffset,SpringArm_SocketOffset,GetWorld()->GetDeltaSeconds(),2.f));
	
}
