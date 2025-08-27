#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolRoute.generated.h"

UCLASS()
class DEBT_API APatrolRoute : public AActor
{
	GENERATED_BODY()

public:

	APatrolRoute();

protected:

	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USplineComponent* PatrolSpline;

	UPROPERTY()
	int PatrolIndex;

	UPROPERTY(meta = (ClampMin = "-1.0", ClampMax = "1.0"))
	int Direction;





	UFUNCTION()
	void IncrementPatrolRoute();

	UFUNCTION()
	FVector GetSplinePointAsWorldPosition() const;


};

