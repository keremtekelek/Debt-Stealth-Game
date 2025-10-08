#include "Actors/HeadLampCPP.h"


AHeadLampCPP::AHeadLampCPP()
{
	PrimaryActorTick.bCanEverTick = true;

	HeadLamp_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadLamp Mesh"));
	RootComponent = HeadLamp_Mesh;

	HeadLamp_Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("HeadLamp Light"));
	HeadLamp_Light->SetupAttachment(HeadLamp_Mesh);

}


void AHeadLampCPP::BeginPlay()
{
	Super::BeginPlay();
	
}


void AHeadLampCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

