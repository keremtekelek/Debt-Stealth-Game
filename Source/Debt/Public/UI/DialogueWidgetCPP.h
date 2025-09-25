#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "DialogueWidgetCPP.generated.h"

/**
 * 
 */
UCLASS()
class DEBT_API UDialogueWidgetCPP : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	//VARIABLES!!!

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DialogueTextBlock;

	UPROPERTY(meta = (BindWidget))
	UBorder* DialogueBorder;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel_Root;

	
};
