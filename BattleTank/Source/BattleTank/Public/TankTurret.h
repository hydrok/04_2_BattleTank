// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent)) //meta=... is the finishing touch to have this appear in the component list.
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void RotateTurret(float TurretRelativeSpeed); //intent is to make speed between -1 and 1

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float TurretMaxDegreesPerSecond = 25; //sensible default
};
