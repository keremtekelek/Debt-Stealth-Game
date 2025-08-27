

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISightTargetInterface.h"
#include "Enums/GlobalEnums.h"
#include "MainCharacter.generated.h"


UCLASS()
class DEBT_API AMainCharacter : public ACharacter, public IAISightTargetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true")) //Making variables of the input actions
	UInputAction* IA_Sprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Crouch;


public:

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAISense_Sight::EVisibilityResult CanBeSeenFrom(const FCanBeSeenFromContext& Context, FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested, float& OutSightStrength, int32* UserData = nullptr, const FOnPendingVisibilityQueryProcessedDelegate* Delegate = nullptr) override;




	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)  //Making the variables of crouch-sprint boolean stations
	bool bIsCrouchingg;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsSprintingg;

	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComp;

	





	UFUNCTION()
	void IA_SPRINT_STARTED(const FInputActionInstance& Instance);  //Created for "started" events of input actions
	void IA_CROUCH_STARTED(const FInputActionInstance& Instance);





};