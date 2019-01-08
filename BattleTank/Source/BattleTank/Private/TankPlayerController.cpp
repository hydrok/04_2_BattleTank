// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() //virtual and void are removed here because they arent needed.
{
	Super::BeginPlay(); //call default behaviour before anything else.
	UE_LOG(LogTemp, Warning, TEXT("PlayerController has initialized")); //this is a logout message useful for debugging.
	auto ControlledTank = GetControlledTank(); //variable created for logging and debugging purposes, is the function finding a tank?
	if (!ControlledTank) //if nothing returned from ControlledTank function
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessed a ControlledTank")); //make a log.
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing %s"), *(ControlledTank->GetName())); //log the tank that is possessed.
		// the *ControlledTank->GetName() means call the GetName function (which comes from a parent class) from the actior that was retruned
		//from the ControlledTank = GetControlledTank() which is also Cast<ATank>(GetPawn())
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Tick Tock")); //log the tick. this has been commented out for ease of debugging
	AimTowardsCrosshair(); //this is the function to deproject the reticule to the world space and return vital information needed for aiming
	//and visual feedback (like the turrent and barrel moving towards the world coordinates of the reticule
}

ATank* ATankPlayerController::GetControlledTank() const 
//this is a "getter". Get value pointed to by GetControlledTank() of type ATank.
// the ATankPlayerController:: part makes the reference specificically from TankPlayerController.h, I think...
{
	//The TankPlayerController needs to know what tank it is controlling.
	return Cast<ATank>(GetPawn()); //this CAST syntax asks to run GetPawn() from ATank...I think...
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}
	else
	{
		FVector OutHitLocation; //Out parameter, this is a FVector type variable
		if (GetSightRayHitLocation(OutHitLocation)) //this will eventually ray-trace as well, which we neeeeeeeed
		{		
			UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *OutHitLocation.ToString()); //The OutHitLocation.ToString() is just like other variables
			//get world location of linetrace through crosshair
			//if it hits landscape
			//tell the player controlled tank to aim toward that point
		}
	}
}
//this function is a boolean but it will also get world location of linetrace through crosshair
//will be true if it hits landscape.
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	OutHitLocation = FVector(1.0); //initialization for testing
	return true; //initialization for testing
}