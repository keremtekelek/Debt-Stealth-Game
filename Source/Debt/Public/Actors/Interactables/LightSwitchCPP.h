#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Light.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/LightComponent.h"
#include "Components/SceneComponent.h"
#include "Materials/MaterialInterface.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundAttenuation.h"
#include "Interfaces/Interface_Interaction.h"
#include "LightSwitchCPP.generated.h"

UCLASS()
class DEBT_API ALightSwitchCPP : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()
	
public:	
	
	ALightSwitchCPP();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

	//VARIABLES!!

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
	FName RoomName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* MI_Lamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* SwitchSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundAttenuation* SwitchSoundAttenuation;

	UPROPERTY(VisibleAnywhere)
	bool CanInteract;

	UPROPERTY(VisibleAnywhere)
	bool IsLightOpen = true;

	UPROPERTY(VisibleAnywhere)
	bool FlipFlopVariable = true;

	UPROPERTY(VisibleAnywhere)
	float EmissiveLightValue = 340.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	float SwitchSoundVolume = 1.5f;

	UPROPERTY(VisibleAnywhere)
	TArray<float> OriginalLightIntensities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lights")
	TArray<ALight*> RelatedLights;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	TArray<AStaticMeshActor*> RelatedLamps;

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
	UStaticMeshComponent* SwitchMesh;





	//FUNCTIONS!!!

	UFUNCTION()
	void OpenTheLights();

	UFUNCTION()
	void CloseTheLights();

	UFUNCTION()
	void GetPreviousLightIntensities();

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

};
