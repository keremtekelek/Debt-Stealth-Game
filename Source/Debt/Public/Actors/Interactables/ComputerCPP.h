#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/ComputerScreenCPP.h"
#include "TimerManager.h" 
#include "Interfaces/Interface_Interaction.h"
#include "ComputerCPP.generated.h"

UCLASS()
class DEBT_API AComputerCPP : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()
	
public:	

	AComputerCPP();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation() override;

	//VARIABLES!!!

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
	FName RoomName;

	UPROPERTY(VisibleAnywhere)
	bool CanInteract;

	UPROPERTY(VisibleAnywhere)
	bool IsComputerOpen = false;

	UPROPERTY(VisibleAnywhere)
	bool FlipFlopVariable = true;

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
	UStaticMeshComponent* ComputerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* WidgetComp;

	UPROPERTY()
	UComputerScreenCPP* ComputerScreenWidget;

	UPROPERTY()
	FTimerHandle DelayHandler;


	//FUNCTIONS!!!

	UFUNCTION()
	void GetWidget();

	UFUNCTION()
	void OpenTheComputer();

	UFUNCTION()
	void CloseTheComputer();

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
