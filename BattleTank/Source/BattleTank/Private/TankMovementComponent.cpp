// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) 
	{
		return;
	}
	LeftTrack->SetThrottle(Throw); //call set throttle from tanktrack.cpp
	RightTrack->SetThrottle(Throw); //call set throttle from tanktrack.cpp
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	LeftTrack->SetThrottle(Throw); //call set throttle from tanktrack.cpp
	RightTrack->SetThrottle(-Throw); //the minus here is to "offset" the positive to make a right turn.
}

void UTankMovementComponent::Initialise(UTankTrack*LeftTrackToSet, UTankTrack*RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}