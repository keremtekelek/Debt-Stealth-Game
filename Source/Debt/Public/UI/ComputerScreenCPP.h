#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "ComputerScreenCPP.generated.h"

/**
 * 
 */
UCLASS()
class DEBT_API UComputerScreenCPP : public UUserWidget
{
	GENERATED_BODY()

public:

	/*
	UPROPERTY(meta = (BindWidget))
	UImage* ComputerScreenImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel_Root;
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsComputerInteractable = true;

	

	// FUNCTIONS!!!

	UFUNCTION(BlueprintImplementableEvent)
	void OpenVideo();

	UFUNCTION(BlueprintImplementableEvent)
	void CloseVideo();

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	
};
