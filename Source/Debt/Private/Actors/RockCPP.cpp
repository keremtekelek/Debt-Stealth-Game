#include "Actors/RockCPP.h"

// Sets default values
ARockCPP::ARockCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	// Creating Default SubObjects
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = SphereCollision;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock Mesh"));
	StaticMesh->SetupAttachment(SphereCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	StimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSourceComp"));
	StimuliSourceComp->bAutoRegister = true;


	// Defining the Default Values of Variables
	
}

// Called when the game starts or when spawned
void ARockCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARockCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARockCPP::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StimuliSourceComp->RegisterForSense(UAISense_Sight::StaticClass());
	StimuliSourceComp->RegisterWithPerceptionSystem();

}



