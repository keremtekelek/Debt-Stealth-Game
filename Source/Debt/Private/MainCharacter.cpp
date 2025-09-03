#include "MainCharacter.h"



AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsCrouchingg = false; //Setting the Variables default values 
	bIsSprintingg = false;

	static ConstructorHelpers::FObjectFinder<UInputAction> SprintAction(TEXT("/Game/Input/Actions/IA_Sprint")); //Getting IA_Sprint and IA_Crouch
	static ConstructorHelpers::FObjectFinder<UInputAction> CrouchAction(TEXT("/Game/Input/Actions/IA_Crouch"));

	if (SprintAction.Succeeded())			//If it succeeds, equalizing the SprintAction with input actions
	{
		IA_Sprint = SprintAction.Object;
	}
	else									//If fails, equalizing the input actions to nullptr
	{
		IA_Sprint = nullptr;
	}
	if (CrouchAction.Succeeded())
	{
		IA_Crouch = CrouchAction.Object;
	}
	else
	{
		IA_Crouch = nullptr;
	}
}


void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharacterMovementComp = GetCharacterMovement();  //Setting the CharacterMovementComp variable

	CharacterMovementComp->MaxWalkSpeed = 300.f;
}


void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) //Getting the Enhanced Input System and binding the input actions named "started"
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Sprint)
		{
			EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AMainCharacter::IA_SPRINT_STARTED);
		}

		if (IA_Crouch)
		{
			EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Started, this, &AMainCharacter::IA_CROUCH_STARTED);
		}
	}
}



void AMainCharacter::IA_SPRINT_STARTED(const FInputActionInstance& Instance) // Setting the IA_Sprint's "Started" event
{
	if (!(bIsCrouchingg))
	{
		if (bIsSprintingg)
		{
			bIsSprintingg = false;
			if (CharacterMovementComp)
			{
				CharacterMovementComp->MaxWalkSpeed = 300.f;
			}
		}
		else
		{
			bIsSprintingg = true;

			if (CharacterMovementComp)
			{
				CharacterMovementComp->MaxWalkSpeed = 600.f;
			}
		}
	}
}


void AMainCharacter::IA_CROUCH_STARTED(const FInputActionInstance& Instance) //Setting the IA_Crouch's "Started" event
{
	if (!(bIsSprintingg))
	{
		if (!(bIsCrouchingg))
		{
			bIsCrouchingg = true;
			Crouch();
		}
		else
		{
			bIsCrouchingg = false;
			UnCrouch();
		}
	}
}


/**
	 * The method needs to check whether the implementer is visible from given observer's location.
	 * This version allows an asynchronous answer by returning Pending and using the provided Delegate when the information is computed
	 * @param Context								Struct containing all the information required to perform the query
	 * @param OutSeenLocation						The first visible target location
	 * @param OutNumberOfLoSChecksPerformed			The number of synchronous queries done. This is used to stop the perception tick sooner when too many LoS checks are done
	 * @param OutNumberOfAsyncLosCheckRequested		The number of asynchronous queries done. This is used to stop the perception tick sooner when too many asynchronous LoS checks are done
	 * @param OutSightStrength						The sight strength for how well the target is seen
	 * @param UserData								If available, it is a data passed between visibility tests for the users to store whatever they want
	 * @param Delegate								If available, the delegate to call later on, if the result needed asynchronous checks. Calling this delegate within the CanBeSeenFrom call will ensure
	 * @return										Undefined to indicate that we need to try another CanBeSeenFrom implementation, Visible/NotVisible if visible/not visible from the observer's location, Pending if the check is not finished
	 */




UAISense_Sight::EVisibilityResult AMainCharacter::CanBeSeenFrom(
	const FCanBeSeenFromContext& Context,
	FVector& OutSeenLocation,
	int32& OutNumberOfLoSChecksPerformed,
	int32& OutNumberOfAsyncLosCheckRequested,
	float& OutSightStrength,
	int32* UserData,
	const FOnPendingVisibilityQueryProcessedDelegate* Delegate
)
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));
	FHitResult HitResult;

	FCollisionQueryParams Params(NAME_AILineOfSight, true, Context.IgnoreActor);


	const FName prioritySocket = FName(TEXT("head"));
	if (GetMesh()->DoesSocketExist(prioritySocket))
	{
		FVector prioritySocketLocation = GetMesh()->GetSocketLocation(prioritySocket);
		bool bHitPrioritySocket = GetWorld()->LineTraceSingleByObjectType(
			HitResult,
			Context.ObserverLocation,
			prioritySocketLocation,
			FCollisionObjectQueryParams(ECC_WorldStatic | ECC_WorldDynamic),
			Params
		);
		OutNumberOfLoSChecksPerformed++;

		if (!bHitPrioritySocket || (IsValid(HitResult.GetActor()) && HitResult.GetActor()->IsOwnedBy(this)))
		{
			OutSeenLocation = prioritySocketLocation;
			OutSightStrength = 1;
			return UAISense_Sight::EVisibilityResult::Visible;
		}
	}


	auto sockets = GetMesh()->GetAllSocketNames();
	for (const auto& SocketName : sockets)
	{
		if (SocketName == prioritySocket) continue;

		FVector SocketLoc = GetMesh()->GetSocketLocation(SocketName);

		bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(
			HitResult,
			Context.ObserverLocation,
			SocketLoc,
			FCollisionObjectQueryParams(ECC_WorldStatic | ECC_WorldDynamic),
			Params
		);

		OutNumberOfLoSChecksPerformed++;

		if (!bHitSocket || (IsValid(HitResult.GetActor()) && HitResult.GetActor()->IsOwnedBy(this)))
		{
			OutSeenLocation = SocketLoc;
			OutSightStrength = 1;
			return UAISense_Sight::EVisibilityResult::Visible;
		}
	}


	const bool bHitBody = GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		Context.ObserverLocation,
		GetActorLocation(),
		FCollisionObjectQueryParams(ECC_WorldStatic | ECC_WorldDynamic),
		Params
	);

	OutNumberOfLoSChecksPerformed++;

	if (!bHitBody || (IsValid(HitResult.GetActor()) && HitResult.GetActor()->IsOwnedBy(this)))
	{
		OutSeenLocation = GetActorLocation();
		OutSightStrength = 1;
		return UAISense_Sight::EVisibilityResult::Visible;
	}

	OutSightStrength = 0;
	return UAISense_Sight::EVisibilityResult::NotVisible;
}





















