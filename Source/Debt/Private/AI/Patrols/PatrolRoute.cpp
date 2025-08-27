#include "AI/Patrols/PatrolRoute.h"
#include "Components/SplineComponent.h"

APatrolRoute::APatrolRoute()
{
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	PatrolSpline = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolSpline"));
	PatrolSpline->SetupAttachment(RootComponent);

}

void APatrolRoute::BeginPlay()
{
	Super::BeginPlay();

}

void APatrolRoute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APatrolRoute::IncrementPatrolRoute()
{
	PatrolIndex += Direction;


	if ((PatrolSpline->GetNumberOfSplinePoints() - 1) == PatrolIndex)
	{
		Direction = -1;
	}

	else
	{
		if (PatrolIndex == 0)
		{
			Direction = 1;
		}
	}

}

FVector APatrolRoute::GetSplinePointAsWorldPosition() const
{
	return PatrolSpline->GetLocationAtSplinePoint(PatrolIndex, ESplineCoordinateSpace::World);

}

