#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Interfaces/Interface_Interaction.h"
#include "BookCPP.generated.h"

UCLASS()
class DEBT_API ABookCPP : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()
	
public:	
	
	ABookCPP();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	// Variables!!!

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
	FName RoomName;

	UPROPERTY(VisibleAnywhere)
	bool IsBookDestroyed = false;

	UPROPERTY(VisibleAnywhere)
	bool HasInteractedBefore = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* SmallSphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* BigSphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BookMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBillboardComponent* InteractionIcon_BigSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBillboardComponent* InteractionIcon_SmallSphere;

	UPROPERTY(VisibleAnywhere)
	bool CanInteract;


	// Functions!!!
	UFUNCTION()
	void OnBigSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSmallSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBigSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnSmallSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Interact_Implementation() override;
};
