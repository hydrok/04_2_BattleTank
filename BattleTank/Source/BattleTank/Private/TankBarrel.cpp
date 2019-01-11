// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Math/UnrealMathUtility.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	//rotate turret to aim direction in z for one frame (this frame) with a max speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1); //restricts speed within parameters, don't have to redfeine type
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
		//RelativeSpeed bw -1 and 1, MaxDegreesPerSecond set in Tank_BP, DelatTimeSeconds makes this framerate independent
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange; //unbound barrel movement, where would the barrel go if unbound. 
		//RelativeRotation is a property of the scene component, not a defined user variable.
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees); //restricts movement of barrel.
		//FMath is built in function, and it limits Elevation to be bw Min and Max. SetRelativeRotation will not be able to change th rotation
		//past the limits.
	SetRelativeRotation(FRotator(Elevation, 0 ,0)); //SetRelativeRotation is, again, a property. Function is already defined by UE4 libraries
		//set relative barrel elevation using FRotator.

}

