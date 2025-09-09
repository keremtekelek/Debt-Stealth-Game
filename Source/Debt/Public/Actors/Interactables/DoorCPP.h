#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundAttenuation.h"
#include "Interfaces/Interface_Interaction.h"
#include "DoorCPP.generated.h"

UCLASS()
class DEBT_API ADoorCPP : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()
	
public:	
	
	ADoorCPP();

protected:
	
	virtual void BeginPlay() override;

public:	

	// VARIABLES!!
	
	UPROPERTY(VisibleAnywhere)
	bool CanInteract = false;

	UPROPERTY(VisibleAnywhere)
	bool IsDoorOpen = false;

	UPROPERTY(VisibleAnywhere)
	bool IsPlaying = false;

	UPROPERTY(VisibleAnywhere)
	bool FlipFlopVariable = true;

	UPROPERTY(VisibleAnywhere)
	float DotProductResult = 0.f;

	UPROPERTY(VisibleAnywhere)
	float DoorStartFloat = 0.f;

	UPROPERTY(VisibleAnywhere)
	float DoorEndFloat = 90.f;

	UPROPERTY(EditAnywhere)
	float DoorSoundVolume = 1.f;

	UPROPERTY(EditAnywhere)
	FVector PositiveIconLocation;

	UPROPERTY(EditAnywhere)
	FVector NegativeIconLocation;

	UPROPERTY(VisibleAnywhere)
	ACharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* DoorOpenSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* DoorCloseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundAttenuation* DoorSoundAttenuation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* SmallSphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* BigSphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBillboardComponent* InteractionIcon_BigSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBillboardComponent* InteractionIcon_SmallSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY()
	FTimeline DoorTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;


	//FUNCTIONS!!

	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;


	UFUNCTION()
	void OpenTheDoor();

	UFUNCTION()
	float CalculateDotProduct();
	

	UFUNCTION()
	void OnBigSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBigSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnSmallSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSmallSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void HandleProgress(float Value);

	UFUNCTION()
	void HandleFinished();

};
