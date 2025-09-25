#pragma once
#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"
#include "Enums/GlobalEnums.h"
#include "BlackboardValueFilter.generated.h"

USTRUCT(BlueprintType)
struct DEBT_API FBlackboardValueFilter: public FTableRowBase
{
	GENERATED_BODY()

	// VARIABLES!!

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemySitutation Enemy_Situation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemy_SuspiciousReason Enemy_Investigate_Reason;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemy_AlarmLevel Enemy_AlarmLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemy_HeardReason Enemy_HeardReason;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHeardFootStepMovementType Heard_FootStepMovement_Types;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESuspectedObject SuspectedObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEventRoom EventRooms;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SawRock = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RockSeenInTheAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlayerLostConfirmed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PlayerSawConfirmed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPlayerVisible = false;

};