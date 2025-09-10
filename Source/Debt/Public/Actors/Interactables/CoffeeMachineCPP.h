#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundAttenuation.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "TimerManager.h"
#include "Interfaces/Interface_Interaction.h"
#include "CoffeeMachineCPP.generated.h"

UCLASS()
class DEBT_API ACoffeeMachineCPP : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()
	
public:	
	
	ACoffeeMachineCPP();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation() override;

	//VARIABLES!!

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
	FName RoomName;

	UPROPERTY(VisibleAnywhere)
	bool CanInteract;

	UPROPERTY(VisibleAnywhere)
	bool FlipFlopVariable = true;

	UPROPERTY(VisibleAnywhere)
	bool HasInteractedBefore = false;

	UPROPERTY(VisibleAnywhere)
	bool IsCoffeeMachineCrashed = false;

	UPROPERTY(EditAnywhere)
	float ErrorSoundVolume = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* MachineErrorSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundAttenuation* MachineSoundAttenuation;

	UPROPERTY()
	FTimerHandle DelayHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* NiagaraComp;

	// Niagara System referansý (asset)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* CoffeeNiagaraSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* SmallBoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BigBoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBillboardComponent* InteractionIcon_BigBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBillboardComponent* InteractionIcon_SmallBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* CoffeeMachineMesh;

	//FUNCTIONS!

	UFUNCTION()
	void OnBigBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBigBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnSmallBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSmallBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OpenCoffeeMachine();

	UFUNCTION()
	void CloseNiagara();

};
