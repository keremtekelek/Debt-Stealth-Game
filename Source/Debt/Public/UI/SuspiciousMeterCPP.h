#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "SuspiciousMeterCPP.generated.h"

/**
 * 
 */
UCLASS()
class DEBT_API USuspiciousMeterCPP : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:

	/*
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> Question_Mark;

	UPROPERTY(meta = (BindWidget))
	UImage* ExclamationMarkImage;
	*/
	
public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> Question_Mark;

	UPROPERTY(meta = (BindWidget))
	UImage* ExclamationMarkImage;

	
};
