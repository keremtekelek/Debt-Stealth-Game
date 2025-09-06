#include "Actors/Interactables/BookCPP.h"


ABookCPP::ABookCPP()
{
	PrimaryActorTick.bCanEverTick = true;

	BookMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Book Mesh"));
	RootComponent = BookMesh;

	BigSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Big Sphere Collision"));
	BigSphereCollision->SetupAttachment(BookMesh);

	SmallSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Small Sphere Collision"));
	SmallSphereCollision->SetupAttachment(BookMesh);

	InteractionIcon_BigSphere = CreateDefaultSubobject<UBillboardComponent>(TEXT("Big Sphere Interaction Icon"));
	InteractionIcon_BigSphere->SetupAttachment(RootComponent);

	InteractionIcon_SmallSphere = CreateDefaultSubobject<UBillboardComponent>(TEXT("Small Sphere Interaction Icon"));
	InteractionIcon_SmallSphere->SetupAttachment(RootComponent);


	BigSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABookCPP::OnBigSphereBeginOverlap);
	BigSphereCollision->OnComponentEndOverlap.AddDynamic(this, &ABookCPP::OnBigSphereEndOverlap);

	SmallSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABookCPP::OnSmallSphereBeginOverlap);
	SmallSphereCollision->OnComponentEndOverlap.AddDynamic(this, &ABookCPP::OnSmallSphereEndOverlap);

	//Defining default values on variables

	CanInteract = false;
}


void ABookCPP::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABookCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABookCPP::OnBigSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->ActorHasTag(TEXT("MainCharacter")))
		{
			if (IsValid(InteractionIcon_BigSphere))
			{
				InteractionIcon_BigSphere->SetHiddenInGame(false);
			}
		}
	}
}

void ABookCPP::OnBigSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->ActorHasTag(TEXT("MainCharacter")))
		{
			if (IsValid(InteractionIcon_BigSphere))
			{
				InteractionIcon_BigSphere->SetHiddenInGame(true);
			}
		}
	}
}

void ABookCPP::OnSmallSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->ActorHasTag(TEXT("MainCharacter")))
		{
			CanInteract = true;

			if (IsValid(InteractionIcon_SmallSphere) && IsValid(InteractionIcon_BigSphere))
			{
				InteractionIcon_SmallSphere->SetHiddenInGame(false);
				InteractionIcon_BigSphere->SetHiddenInGame(true);
			}
			
		}
	}


}

void ABookCPP::OnSmallSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->ActorHasTag(TEXT("MainCharacter")))
		{
			CanInteract = false;

			if (IsValid(InteractionIcon_SmallSphere) && IsValid(InteractionIcon_BigSphere))
			{
				InteractionIcon_SmallSphere->SetHiddenInGame(true);
				InteractionIcon_BigSphere->SetHiddenInGame(false);
			}

		}
	}
}



// Interface Functions

void ABookCPP::Interact_Implementation()
{
	if (CanInteract)
	{
		UE_LOG(LogTemp, Warning, TEXT("Book has been Interacted!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Book Interaction Denied!"));
	}
	
}

