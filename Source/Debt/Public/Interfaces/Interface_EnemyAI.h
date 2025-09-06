// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Debt.h"
#include "AI/Patrols/PatrolRoute.h"
#include "Interface_EnemyAI.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_EnemyAI : public UInterface
{
	GENERATED_BODY()
};


class DEBT_API IInterface_EnemyAI
{
	GENERATED_BODY()

	
public:


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	APatrolRoute* GetPatrolRoute() const;			//Interface function that can deliver de Enemy's PatrolRouteCPP(Spline Comp.) variable.

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) //Interface function that can be set the movement speed of the enemy 
	float SetMovementSpeed(EMovementSpeed MovementSpeedType) const;
};
