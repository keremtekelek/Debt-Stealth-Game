#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "HeadLampCPP.generated.h"

UCLASS()
class DEBT_API AHeadLampCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AHeadLampCPP();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HeadLamp_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpotLightComponent* HeadLamp_Light;

};
