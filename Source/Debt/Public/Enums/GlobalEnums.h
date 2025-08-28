// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalEnums.generated.h"

/**
 * 
 */
UCLASS()
class DEBT_API UGlobalEnums : public UObject
{
	GENERATED_BODY()

public:

	
	
	
};

// ENUMS ABOUT ENEMY

//ENUM for Enemy Situtation(Patrol, Investigate, Alarm, LifeCycle, Alarm)

UENUM(BlueprintType)
enum class EEnemySitutation : uint8
{
	None		UMETA(DisplayName = "None"),
	LifeCycle	UMETA(DisplayName = "LifeCycle"),
	Patrol		UMETA(DisplayName = "Patrol"),
	Investigate UMETA(DisplayName = "Investigate"),
	Alarm		UMETA(DisplayName = "Alarm")
};





//ENUM for Investigate Reason (Saw, Hear, Smell, Touch, Damage)
UENUM(BlueprintType)
enum class EEnemy_SuspiciousReason : uint8
{
	None	UMETA(DisplayName = "None"),
	Smell   UMETA(DisplayName = "Smell"),
	Touch	UMETA(DisplayName = "Touch"),
	Damage	UMETA(DisplayName = "Damage"),
	Heard	UMETA(DisplayName = "Heard"),
	Saw		UMETA(DisplayName = "Saw")
};



//ENUM for Enemy Alarm Level (Huge, Big, Middle, Small)

UENUM(BlueprintType)
enum class EEnemy_AlarmLevel : uint8
{
	None		UMETA(DisplayName = "None"),
	SmallAlarm	UMETA(DisplayName = "SmallAlarm"),
	MiddleAlarm UMETA(DisplayName = "MiddleAlarm"),
	BigAlarm	UMETA(DisplayName = "BigAlarm"),
	HugeAlarm	UMETA(DisplayName = "HugeAlarm")
	
};

UENUM(BlueprintType)
enum class EEnemy_HeardReason : uint8
{

	None		UMETA(DisplayName = "None"),
	PulseSound	UMETA(DisplayName = "PulseSound"),
	RockSound   UMETA(DisplayName = "RockSound"),
	FootStep	UMETA(DisplayName = "FootStep")
	
};


// Enum for SuspiciousMeter

UENUM(BlueprintType)
enum class ESuspiciousMeterType : uint8
{

	None		  UMETA(DisplayName = "None"),
	Suspicion	  UMETA(DisplayName = "Suspicion"),
	Investigation UMETA(DisplayName = "Investigation")
	
};


// ENUMS ABOUT ENVIRONMENT AI


UENUM(BlueprintType)
enum class EHeardMaterialType : uint8
{

	None		UMETA(DisplayName = "None"),
	Default		UMETA(DisplayName = "Default"),
	Metal		UMETA(DisplayName = "Metal"),
	Concrete	UMETA(DisplayName = "Concrete")
	
};


UENUM(BlueprintType)
enum class EHeardFootStepMovementType : uint8
{

	None		UMETA(DisplayName = "None"),
	Crouch		UMETA(DisplayName = "Crouch"),
	Walk		UMETA(DisplayName = "Walk"),
	Sprint		UMETA(DisplayName = "Sprint")

};


// DEPRECATED
UENUM(BlueprintType)
enum class DetectionMeter_Style : uint8
{
	Directly	UMETA(DisplayName = "Directly"),
	StepByStep	UMETA(DisplayName = "StepByStep"),
	None		UMETA(DisplayName = "None")
	
};


UENUM(BlueprintType)
enum class DetectionMeter_Reason : uint8
{
	SawThePlayer			UMETA(DisplayName = "SawThePlayer"),
	SawTheSuspiciousObject	UMETA(DisplayName = "SawTheSuspiciousObject"),
	HeardTheFootStep		UMETA(DisplayName = "HeardTheFootStep"),
	None					UMETA(DisplayName = "None")

};
