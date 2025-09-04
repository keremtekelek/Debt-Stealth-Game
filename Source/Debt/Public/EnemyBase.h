
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/Patrols/PatrolRoute.h"
#include "Interfaces/Interface_EnemyAI.h"
#include "Enums/GlobalEnums.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/PlayerCameraManager.h"
#include "TimerManager.h"
#include "EnemyBase.generated.h"



UCLASS()
class DEBT_API AEnemyBase : public ACharacter, public IInterface_EnemyAI
{
	GENERATED_BODY()

public:

	AEnemyBase();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* WidgetComp;
	

protected:

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

private:
	
public:

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//VARIABLES!!!

	//Creating variables for can be seen on the editor and can take a passed value
	UPROPERTY(EditAnywhere, Category = "AAAAA")
	APatrolRoute* PatrolRoute;

	//And this variable is can take a passed value. Also determines the Default value of the EEnemySitutation ENUM value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAAAA")
	EEnemySitutation DefaultEnemySitutation;

	UPROPERTY(VisibleAnywhere)
	ACharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere)
	APlayerCameraManager* CameraManager;

	UPROPERTY(VisibleAnywhere)
	FTimerHandle DelayHandler;
	





	//FUNCTIONS!!!

	

	virtual APatrolRoute* GetPatrolRoute_Implementation() const override;

	virtual float SetMovementSpeed_Implementation(EMovementSpeed MovementSpeedType) const override;

	UFUNCTION()
	void GetProperties();

};
