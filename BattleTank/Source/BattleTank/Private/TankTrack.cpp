// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "Components/SceneComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	//drive the tracks
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels(); //the function defined in the header
	auto ForcePerWheel = ForceApplied / Wheels.Num(); //Wheels.Num is the count of wheels in the array of function GetWheels()

	for (ASprungWheel * Wheel : Wheels) //for each UStaticMeshComponent * Wheel, add a driving force as calcd by ForcePerWheel
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray; //create an array for the wheels (it will probably get other stuff too)
	TArray<USceneComponent*> Children; //build an array called children for UScene Components. 
							//because we are in TankTrack, it will get the children of the tank tracks.
	GetChildrenComponents(true, Children); //get the children and grandchildren of the tracks.
	for (USceneComponent* Child : Children) //iterate through Child : Children
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child); //treats the Child as a USpawnPoint Type??
		if (!SpawnPointChild) { continue; }
		AActor * SpawnedChild = SpawnPointChild->GetSpawnedActor(); //if SpawnPointChild has actor(s)
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild); //treat spawned child as ASprungWheel
		if (!SprungWheel) { continue; }
		ResultArray.Add(SprungWheel); //add to array
		//logic is
			//get spawnpoint
			//get children of spawn point
			//add result to array

	}

	return ResultArray;
}