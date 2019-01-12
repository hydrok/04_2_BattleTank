// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Math/UnrealMathUtility.h"

void UTankTurret::RotateTurret(float TurretRelativeSpeed)
{
	//rotate turret to aim direction in z for one frame (this frame) with a max speed
	TurretRelativeSpeed = FMath::Clamp<float>(TurretRelativeSpeed, -1, 1); //restricts speed within parameters, don't have to redfeine type
	auto RotationChange = TurretRelativeSpeed * TurretMaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	//RelativeSpeed bw -1 and 1, MaxDegreesPerSecond set in Tank_BP, DelatTimeSeconds makes this framerate independent
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange; //unbound barrel movement, where would the barrel go if unbound. 
		//RelativeRotation is a property of the scene component, not a defined user variable.
	
		//clamp is not needed because the turret can go 360 degrees

	SetRelativeRotation(FRotator(0, RawNewRotation, 0)); //SetRelativeRotation is, again, a property. Function is already defined by UE4 libraries
		//set relative barrel elevation using FRotator. had to change the poisitons of RawNewRotation

}