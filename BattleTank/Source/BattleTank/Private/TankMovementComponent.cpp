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

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
//never explained what these are and how thery are populated or needed.
{
	auto TankName = GetOwner()->GetName();
	auto MoveVelocityString = MoveVelocity.ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s moving %s"), *TankName, *MoveVelocityString)
}