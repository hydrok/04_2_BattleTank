// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend to move forward: %f"), Throw);

	LeftTrack->SetThrottle(Throw); //call set throttle from tanktrack.cpp
	RightTrack->SetThrottle(Throw); //call set throttle from tanktrack.cpp

}

void UTankMovementComponent::Initialise(UTankTrack*LeftTrackToSet, UTankTrack*RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) //if OR
	{
		return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}