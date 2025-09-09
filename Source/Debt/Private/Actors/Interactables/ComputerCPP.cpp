#include "Actors/Interactables/ComputerCPP.h"


AComputerCPP::AComputerCPP()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;

	ComputerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Computer Mesh"));
	ComputerMesh->SetupAttachment(RootComponent);

	InteractionIcon_BigBox = CreateDefaultSubobject<UBillboardComponent>(TEXT("Big Box Interaction Icon"));
	InteractionIcon_BigBox->SetupAttachment(ComputerMesh);

	InteractionIcon_SmallBox = CreateDefaultSubobject<UBillboardComponent>(TEXT("Small Box Interaction Icon"));
	InteractionIcon_SmallBox->SetupAttachment(ComputerMesh);

	BigBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Big Box Collsion"));
	BigBoxCollision->SetupAttachment(RootComponent);

	SmallBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Small Box Collsion"));
	SmallBoxCollision->SetupAttachment(RootComponent);

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Computer Screen Widget"));
	if (WidgetComp)
	{
		WidgetComp->SetupAttachment(RootComponent);
		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass{ TEXT("/Game/01_MyContent/Blueprints/UI/WBP_ComputerScreen") };
		if (WidgetClass.Succeeded())
		{
			WidgetComp->SetWidgetClass((WidgetClass.Class));
		}
	}
	

	BigBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AComputerCPP::OnBigBoxBeginOverlap);
	BigBoxCollision->OnComponentEndOverlap.AddDynamic(this, &AComputerCPP::OnBigBoxEndOverlap);

	SmallBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AComputerCPP::OnSmallBoxBeginOverlap);
	SmallBoxCollision->OnComponentEndOverlap.AddDynamic(this, &AComputerCPP::OnSmallBoxEndOverlap);
}


void AComputerCPP::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetComp)
	{
		WidgetComp->InitWidget();
	}

	GetWorldTimerManager().SetTimer(DelayHandler, this, &AComputerCPP::GetWidget, 1.5f, false);
	
}


void AComputerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AComputerCPP::OnBigBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->ActorHasTag(TEXT("MainCharacter")))
		{
			if (IsValid(InteractionIcon_BigBox))
			{
				InteractionIcon_BigBox->SetHiddenInGame(false);
			}
		}
	}
}

void AComputerCPP::OnBigBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->ActorHasTag(TEXT("MainCharacter")))
		{
			if (IsValid(InteractionIcon_BigBox))
			{
				InteractionIcon_BigBox->SetHiddenInGame(true);
			}
		}
	}
}

void AComputerCPP::OnSmallBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->ActorHasTag(TEXT("MainCharacter")))
		{
			CanInteract = true;

			if (IsValid(InteractionIcon_SmallBox) && IsValid(InteractionIcon_BigBox))
			{
				InteractionIcon_SmallBox->SetHiddenInGame(false);
				InteractionIcon_BigBox->SetHiddenInGame(true);
			}
		}
	}
}

void AComputerCPP::OnSmallBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->ActorHasTag(TEXT("MainCharacter")))
		{
			CanInteract = false;

			if (IsValid(InteractionIcon_SmallBox) && IsValid(InteractionIcon_BigBox))
			{
				InteractionIcon_SmallBox->SetHiddenInGame(true);
				InteractionIcon_BigBox->SetHiddenInGame(false);
			}
		}
	}
}


void AComputerCPP::GetWidget()
{
	GetWorld()->GetTimerManager().ClearTimer(DelayHandler);

	if (WidgetComp)
	{
		UUserWidget* Widget = WidgetComp->GetWidget();
		if (Widget)
		{
			ComputerScreenWidget = Cast<UComputerScreenCPP>(Widget);
		}
	}
}


void AComputerCPP::OpenTheComputer()
{
	ComputerScreenWidget->OpenVideo();
}

void AComputerCPP::CloseTheComputer()
{
	ComputerScreenWidget->CloseVideo();
}

void AComputerCPP::Interact_Implementation()
{
	if (CanInteract)
	{
		if (FlipFlopVariable)
		{
			OpenTheComputer();

			FlipFlopVariable = false;
		}
		else
		{
			CloseTheComputer();
			FlipFlopVariable = true;
		}
	}
}

