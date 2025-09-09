#include "Actors/Interactables/DoorCPP.h"


ADoorCPP::ADoorCPP()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMesh->SetupAttachment(RootComponent);

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	DoorFrame->SetupAttachment(RootComponent);

	BigSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Big Sphere Collision"));
	BigSphereCollision->SetupAttachment(RootComponent);

	SmallSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Small Sphere Collision"));
	SmallSphereCollision->SetupAttachment(RootComponent);

	InteractionIcon_BigSphere = CreateDefaultSubobject<UBillboardComponent>(TEXT("Big Sphere Interaction Icon"));
	InteractionIcon_BigSphere->SetupAttachment(DoorMesh);

	InteractionIcon_SmallSphere = CreateDefaultSubobject<UBillboardComponent>(TEXT("Small Sphere Interaction Icon"));
	InteractionIcon_SmallSphere->SetupAttachment(DoorMesh);


	BigSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ADoorCPP::OnBigSphereBeginOverlap);
	BigSphereCollision->OnComponentEndOverlap.AddDynamic(this, &ADoorCPP::OnBigSphereEndOverlap);

	SmallSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ADoorCPP::OnSmallSphereBeginOverlap);
	SmallSphereCollision->OnComponentEndOverlap.AddDynamic(this, &ADoorCPP::OnSmallSphereEndOverlap);


	//Defining default values of variables

	PositiveIconLocation= FVector(20.f,-80.f,110.f);
	NegativeIconLocation = FVector(-20.f, -80.f, 110.f);

}


void ADoorCPP::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (CurveFloat)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("HandleProgress"));
		DoorTimeline.AddInterpFloat(CurveFloat, ProgressFunction);
	}
	

	FOnTimelineEvent FinishedFunction;
	FinishedFunction.BindUFunction(this, FName("HandleFinished"));
	DoorTimeline.SetTimelineFinishedFunc(FinishedFunction);
	
}

void ADoorCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorTimeline.TickTimeline(DeltaTime);
	DotProductResult = CalculateDotProduct();

	if (DotProductResult >= 0.f)
	{
		if (InteractionIcon_BigSphere && InteractionIcon_SmallSphere)
		{
			InteractionIcon_BigSphere->SetRelativeLocation(PositiveIconLocation);
			InteractionIcon_SmallSphere->SetRelativeLocation(PositiveIconLocation);
		}
	}
	else
	{
		if (InteractionIcon_BigSphere && InteractionIcon_SmallSphere)
		{
			InteractionIcon_BigSphere->SetRelativeLocation(NegativeIconLocation);
			InteractionIcon_SmallSphere->SetRelativeLocation(NegativeIconLocation);
		}

	}
}

void ADoorCPP::OnBigSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
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

void ADoorCPP::OnBigSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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

void ADoorCPP::OnSmallSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
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

void ADoorCPP::OnSmallSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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

float ADoorCPP::CalculateDotProduct()
{
	if (PlayerCharacter)
	{
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		FVector DoorLocation = GetActorLocation();
		FVector Door_FV = GetActorForwardVector();
		FVector NormalizedValue = PlayerLocation - DoorLocation;

		NormalizedValue.Normalize();
		float Result = FVector::DotProduct(Door_FV, NormalizedValue);

		return Result;
	}
	else
	{
		return 0.f;
	}
}

//Timeline functions

void ADoorCPP::OpenTheDoor()
{
	if (!IsPlaying)
	{
		if (FlipFlopVariable)
		{
			if (DotProductResult >= 0)
			{
				DoorEndFloat = -90.f;
				DoorTimeline.PlayFromStart();
			}
			else
			{
				DoorEndFloat = 90.f;
				DoorTimeline.PlayFromStart();
			}

			if (IsValid(DoorOpenSound) && IsValid(DoorSoundAttenuation))
			{
				FVector DoorLocation = GetActorLocation();
				UGameplayStatics::PlaySoundAtLocation(this, DoorOpenSound, DoorLocation, DoorSoundVolume, 1.f, 0.f, DoorSoundAttenuation);
			}

			FlipFlopVariable = false;
		}
		else
		{

			DoorTimeline.ReverseFromEnd();
			FlipFlopVariable = true;
		}
	}
}

void ADoorCPP::HandleProgress(float Value)
{
	float Rotation = FMath::Lerp(DoorStartFloat, DoorEndFloat, Value);

	FRotator  NewRotation(0.f,Rotation, 0.f);
	
	DoorMesh->SetRelativeRotation(NewRotation);

	IsPlaying = true;
}

void ADoorCPP::HandleFinished()
{
	IsPlaying = false;

	if (FlipFlopVariable)
	{
		if (IsValid(DoorCloseSound) && IsValid(DoorSoundAttenuation))
		{
			FVector DoorLocation = GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(this, DoorCloseSound, DoorLocation, DoorSoundVolume, 1.f, 0.f, DoorSoundAttenuation);
		}
	}
}


// Interface Functions

void ADoorCPP::Interact_Implementation()
{
	if (CanInteract)
	{
		OpenTheDoor();
	}
}

