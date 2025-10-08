#include "PlayerController/PlayerControllerCPP.h"

APlayerControllerCPP::APlayerControllerCPP()
{
	DialogueWidgetRef = nullptr;

	static ConstructorHelpers::FClassFinder<UDialogueWidgetCPP> WidgetBPClass(TEXT("/Game/01_MyContent/Blueprints/UI/WBP_Dialogue"));
	if (WidgetBPClass.Succeeded())
	{
		DialogueWidgetClass = WidgetBPClass.Class;
	}

	// Adjusting Default Player Camera Manager Class
	PlayerCameraManagerClass = ACameraManagerCPP::StaticClass();
	
}

void APlayerControllerCPP::BeginPlay()
{
	Super::BeginPlay();

   	if (DialogueWidgetClass)
	{
		DialogueWidgetRef = CreateWidget<UDialogueWidgetCPP>(GetWorld(), DialogueWidgetClass);

		if (DialogueWidgetRef)
		{
			DialogueWidgetRef->AddToViewport();
			DialogueWidgetRef->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}



