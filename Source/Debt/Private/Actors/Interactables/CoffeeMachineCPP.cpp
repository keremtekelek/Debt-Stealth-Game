#include "Actors/Interactables/CoffeeMachineCPP.h"


ACoffeeMachineCPP::ACoffeeMachineCPP()
{
 	
	PrimaryActorTick.bCanEverTick = true;


	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;

	CoffeeMachineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coffee Machine Mesh"));
	CoffeeMachineMesh->SetupAttachment(RootComponent);

	InteractionIcon_BigBox = CreateDefaultSubobject<UBillboardComponent>(TEXT("Big Box Interaction Icon"));
	InteractionIcon_BigBox->SetupAttachment(CoffeeMachineMesh);

	InteractionIcon_SmallBox = CreateDefaultSubobject<UBillboardComponent>(TEXT("Small Box Interaction Icon"));
	InteractionIcon_SmallBox->SetupAttachment(CoffeeMachineMesh);

	BigBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Big Box Collsion"));
	BigBoxCollision->SetupAttachment(RootComponent);

	SmallBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Small Box Collsion"));
	SmallBoxCollision->SetupAttachment(RootComponent);

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	NiagaraComp->SetupAttachment(RootComponent);
	NiagaraComp->bAutoActivate = false;
	

	BigBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoffeeMachineCPP::OnBigBoxBeginOverlap);
	BigBoxCollision->OnComponentEndOverlap.AddDynamic(this, &ACoffeeMachineCPP::OnBigBoxEndOverlap);

	SmallBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoffeeMachineCPP::OnSmallBoxBeginOverlap);
	SmallBoxCollision->OnComponentEndOverlap.AddDynamic(this, &ACoffeeMachineCPP::OnSmallBoxEndOverlap);

}


void ACoffeeMachineCPP::BeginPlay()
{
	Super::BeginPlay();
	
	if (CoffeeNiagaraSystem)
	{
		NiagaraComp->SetAsset(CoffeeNiagaraSystem);
	}
}


void ACoffeeMachineCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoffeeMachineCPP::OnBigBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
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

void ACoffeeMachineCPP::OnBigBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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

void ACoffeeMachineCPP::OnSmallBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
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

void ACoffeeMachineCPP::OnSmallBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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

void ACoffeeMachineCPP::OpenCoffeeMachine()
{
	if (IsValid(NiagaraComp))
	{
		NiagaraComp->Activate(true);
	}
	

	if (IsValid(MachineErrorSound) && IsValid(MachineSoundAttenuation))
	{
		FVector CoffeeMachineLocation = GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(this, MachineErrorSound, CoffeeMachineLocation, ErrorSoundVolume, 1.f, 0.f, MachineSoundAttenuation);
	}

	GetWorldTimerManager().SetTimer(DelayHandler, this, &ACoffeeMachineCPP::CloseNiagara, 10.f, false);
}

void ACoffeeMachineCPP::CloseNiagara()
{
	if (IsValid(NiagaraComp))
	{
		NiagaraComp->Deactivate();
	}
}

void ACoffeeMachineCPP::Interact_Implementation()
{
	if (CanInteract && !HasInteractedBefore)
	{
		OpenCoffeeMachine();
		HasInteractedBefore = true;
		IsCoffeeMachineCrashed = true;
	}
}