#pragma once
#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"
#include "DataTables/BlackboardValueFilter.h"
#include "DialogueStruct.generated.h"

USTRUCT(BlueprintType)
struct DEBT_API FDialogueStruct: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AboutDialogue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* DialogueVoice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundAttenuation* DialogueSoundAttenuation;

	UPROPERTY(EditAnywhere)
	float DialogueSoundVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardValueFilter RequiredStates;

};
