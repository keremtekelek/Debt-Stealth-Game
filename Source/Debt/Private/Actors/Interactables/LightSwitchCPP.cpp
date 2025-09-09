#include "Actors/Interactables/LightSwitchCPP.h"


ALightSwitchCPP::ALightSwitchCPP()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Switch Mesh"));
	SwitchMesh->SetupAttachment(RootComponent);

	InteractionIcon_BigBox = CreateDefaultSubobject<UBillboardComponent>(TEXT("Big Box Interaction Icon"));
	InteractionIcon_BigBox->SetupAttachment(SwitchMesh);

	InteractionIcon_SmallBox = CreateDefaultSubobject<UBillboardComponent>(TEXT("Small Box Interaction Icon"));
	InteractionIcon_SmallBox->SetupAttachment(SwitchMesh);

	BigBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Big Box Collsion"));
	BigBoxCollision->SetupAttachment(RootComponent);

	SmallBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Small Box Collsion"));
	SmallBoxCollision->SetupAttachment(RootComponent);

	BigBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchCPP::OnBigBoxBeginOverlap);
	BigBoxCollision->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchCPP::OnBigBoxEndOverlap);

	SmallBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchCPP::OnSmallBoxBeginOverlap);
	SmallBoxCollision->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchCPP::OnSmallBoxEndOverlap);

	
}

void ALightSwitchCPP::BeginPlay()
{
	Super::BeginPlay();

	GetPreviousLightIntensities();
	
}


void ALightSwitchCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightSwitchCPP::OnBigBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
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

void ALightSwitchCPP::OnBigBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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

void ALightSwitchCPP::OnSmallBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
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

void ALightSwitchCPP::OnSmallBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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

void ALightSwitchCPP::OpenTheLights()
{
	
	int32 LightArrayLength = RelatedLights.Num() - 1;

	for (int32 i = 0; i < LightArrayLength; i++)
	{
		ALight* Light = RelatedLights[i];
		float IntensityOfArray = OriginalLightIntensities[i];

		if (IsValid(Light))
		{
			ULightComponent* LightComp = Light->GetLightComponent();


			LightComp->SetIntensity(IntensityOfArray);
		}
	}

	for (AStaticMeshActor* Lamps : RelatedLamps)
	{
		if (IsValid(Lamps))
		{
			UStaticMeshComponent* LampMesh = Lamps->GetStaticMeshComponent();

			if (LampMesh)
			{
				UMaterialInstanceDynamic* LampMaterialInstance = LampMesh->CreateDynamicMaterialInstance(0, MI_Lamp);
				LampMaterialInstance->SetScalarParameterValue(FName("Emission Strength"), EmissiveLightValue);
			}
		}
	}

	FVector SwitchLocation = GetActorLocation();

	if (IsValid(SwitchSound) && IsValid(SwitchSoundAttenuation))
	{
		UGameplayStatics::PlaySoundAtLocation(this, SwitchSound, SwitchLocation, 1.f, 1.f, 0.f, SwitchSoundAttenuation);
	}
}

void ALightSwitchCPP::CloseTheLights()
{
	for (ALight* Lights : RelatedLights)
	{
		if (IsValid(Lights))
		{
			ULightComponent* LightComp = Lights->GetLightComponent();
			if (LightComp)
			{
				LightComp->SetIntensity(0.f);
			}
		}
	}

	for (AStaticMeshActor* Lamps : RelatedLamps)
	{
		if (IsValid(Lamps))
		{
			UStaticMeshComponent* LampMesh = Lamps->GetStaticMeshComponent();

			if (LampMesh)
			{
				UMaterialInstanceDynamic* LampMaterialInstance= LampMesh->CreateDynamicMaterialInstance(0,MI_Lamp);
				LampMaterialInstance->SetScalarParameterValue(FName("Emission Strength"), 0.f);
			}
		}
	}


	FVector SwitchLocation = GetActorLocation();
	
	if (IsValid(SwitchSound) && IsValid(SwitchSoundAttenuation))
	{
		UGameplayStatics::PlaySoundAtLocation(this, SwitchSound, SwitchLocation,1.f,SwitchSoundVolume,0.f,SwitchSoundAttenuation);
	}
	

}

void ALightSwitchCPP::GetPreviousLightIntensities()
{
	for (ALight* Lights : RelatedLights)
	{
		if (IsValid(Lights))
		{
			ULightComponent* LightComp = Lights->GetLightComponent();

			if (LightComp)
			{
				float Intensities = LightComp->Intensity;
				OriginalLightIntensities.Add(Intensities);
			}
		}
	}
}

void ALightSwitchCPP::Interact_Implementation()
{
	if (CanInteract)
	{
		if (FlipFlopVariable)
		{
			CloseTheLights();
			IsLightOpen = false;

			FlipFlopVariable = false;
		}
		else
		{
			OpenTheLights();
			IsLightOpen = true;

			FlipFlopVariable = true;
		}
	}
}