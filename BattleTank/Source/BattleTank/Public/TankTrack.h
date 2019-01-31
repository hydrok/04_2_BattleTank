// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SpawnPoint.h"
#include "TankTrack.generated.h"



/**
 * TankTack is set to set max driving force and apply force to tank 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	//this is max force PER TRACK in Newtons.
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 20000000; 

	UTankTrack();

	void DriveTrack(float CurrentThrottle);

private:

	TArray<class ASprungWheel*> GetWheels() const; //getting a list of all the wheels, an arry type
	USpawnPoint * SpawnedSpring;
};
