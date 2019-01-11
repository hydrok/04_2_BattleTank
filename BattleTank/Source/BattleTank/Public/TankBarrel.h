// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

//how do we change the barrel from a static mesh to a class based thing?
//this is important because our code wants to reference classes instead of objects sometimes.
//we want to make sure that TankBarrel appears in the add component section of the Tank_BP
UCLASS(meta = (BlueprintSpawnableComponent)) //meta=... is the finishing touch to have this appear in the component list.
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void ElevateBarrel(float RelativeSpeed); //intent is to make speed between -1 and 1
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 5; //sensible default
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 40; //sensible default
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0; //sensible default
};
