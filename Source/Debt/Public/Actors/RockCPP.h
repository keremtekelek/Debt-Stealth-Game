
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "RockCPP.generated.h"

UCLASS()
class DEBT_API ARockCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ARockCPP();

protected:
	
	virtual void BeginPlay() override;

	

public:	
	
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionStimuliSourceComponent* StimuliSourceComp;

};
