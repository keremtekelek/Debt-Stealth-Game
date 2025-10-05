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
		WidgetComp->SetRelativeLocation(FVector(0, 10, 200));
		WidgetComp->SetVisibility(false);
		WidgetComp->SetHiddenInGame(true);
		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass{ TEXT("/Game/01_MyContent/Blueprints/UI/WBP_SuspiciousMeter") };

		if (WidgetClass.Succeeded())
		{
			WidgetComp->SetWidgetClass((WidgetClass.Class));
		}
	}

	
	
		DialogueSystemComponent = CreateDefaultSubobject<UDialogueSystemCPP>(TEXT("DialogueSystemComponent"));
	
	
	
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	WidgetComp->InitWidget();

	if (DialogueSystemComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialogue System Component is valid!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialogue System Component is NOT valid!"));
	}
	
	
	GetWorld()->GetTimerManager().SetTimer(DelayHandler, this, &AEnemyBase::GetProperties, 2.f, false);
}

void AEnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/**
	* if (IsValid(WidgetComp) && IsValid(PlayerCharacter) && IsValid(CameraManager))
	{
		FRotator LookAtRotation;
		FVector TargetLocation;
		FVector StartLocation;

		StartLocation = WidgetComp->GetComponentLocation();
		TargetLocation = CameraManager->GetTransformComponent()->GetComponentLocation();

		LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);

		WidgetComp->SetWorldRotation(LookAtRotation);
	}
	 */

	if (IsValid(WidgetComp) && IsValid(PlayerCharacter) && IsValid(CameraManager))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Can Widget Seeable?:  %s"), ( CanWidgetBeSeen ? TEXT("true"): TEXT("false") ));
		
		FVector TargetLocation;
		FVector StartLocation;
		FHitResult HitResult;

		StartLocation = WidgetComp->GetComponentLocation();
		TargetLocation = CameraManager->GetCameraLocation();

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this); 
		Params.AddIgnoredActor(PlayerCharacter);

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, TargetLocation, ECC_Visibility,Params);

		if (bHit)
		{
			WidgetComp->SetVisibility(false);
			WidgetComp->SetHiddenInGame(true);
		}
	}
	
	GetWorld()->GetTimerManager().SetTimer(SendRoomNameHandler, this, &AEnemyBase::CallSendRoomName, 0.3f, false);
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

void AEnemyBase::GetProperties()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(DelayHandler);
		PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	}
}

FName AEnemyBase::SendRoomName()
{
	FHitResult HitResult;
	FVector LineTraceStartLoc;
	FVector LineTraceEndLoc;

	LineTraceStartLoc = GetActorLocation();
	LineTraceEndLoc = (GetActorUpVector() * -150) + LineTraceStartLoc;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStartLoc, LineTraceEndLoc, ECC_Visibility);

	if (bHit)
	{
		TArray<FName> RoomName = HitResult.GetComponent()->ComponentTags;
		
		for (FName name : RoomName)
		{
			return name;
		}
	}

	return FName("None");

}

void AEnemyBase::CallSendRoomName()
{
	SendRoomName();
}
