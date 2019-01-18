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
//MoveToActor (in TankAIController) will call this function at some point.
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); //the direction the tank is facing, in unit vector
	auto AIForwardIntention = MoveVelocity.GetSafeNormal(); //getsafenormal is a unit vector, a normalised output
		//this is the direction the AI would like to move the tank, based on pathfinding.

	auto AIForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(AIForwardThrow);
	//UE_LOG(LogTemp, Warning, TEXT("%s moving %s"), *TankName, *AIForwardIntention)
}