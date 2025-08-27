#include "EnemyBase.h"



AEnemyBase::AEnemyBase()
{

	PrimaryActorTick.bCanEverTick = true;

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("SuspiciousMeterWidgett"));

	if (WidgetComp)
	{
		WidgetComp->SetupAttachment(GetMesh());
		WidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComp->SetDrawSize(FVector2D(100, 100));
		WidgetComp->SetRelativeLocation(FVector(0, 0, 180));
		WidgetComp->SetVisibility(false);
		WidgetComp->SetHiddenInGame(true);
		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass{ TEXT("/Game/01_MyContent/Blueprints/UI/WBP_SuspiciousMeter") };

		if (WidgetClass.Succeeded())
		{
			WidgetComp->SetWidgetClass((WidgetClass.Class));
		}

	}
	
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	WidgetComp->InitWidget();

}

void AEnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}


void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}


void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


APatrolRoute* AEnemyBase::GetPatrolRoute_Implementation() const
{
	return PatrolRoute;
}

float AEnemyBase::SetMovementSpeed_Implementation(EMovementSpeed MovementSpeedType) const
{
	float NewSpeed = 0.f;

	switch (MovementSpeedType) {
	case EMovementSpeed::Idle:
		NewSpeed = 0.f;
		break;

	case EMovementSpeed::Walking:
		NewSpeed = 200.f;
		break;

	case EMovementSpeed::Jogging:
		NewSpeed = 400.f;
		break;

	case EMovementSpeed::Sprinting:
		NewSpeed = 550.f;
		break;

	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
	}

	return GetCharacterMovement()->MaxWalkSpeed;

}


