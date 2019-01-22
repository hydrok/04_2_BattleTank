// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//work out the required acceleration this frame
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector(); //makes it a correction to the force
	//calc and apply sideways force (correction) (F= m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) /2 ; //divide 2 because two tracks.
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); //location of the track in question
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

