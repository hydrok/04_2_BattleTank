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
			UE_LOG(LogTemp, Warning, TEXT("OutHitLocation is: %s"), *OutHitLocation.ToString()); //The OutHitLocation.ToString() is just like other variables
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
	//find crosshair position, pixel coordinates
	int32 ViewportSizeX, ViewportSizeY; //size of the current viewport
	GetViewportSize(ViewportSizeX, ViewportSizeY); //gets the size of the viewport and is DYNAMIC
	auto ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);
		//gives the actual pixel location of the crosshair
	UE_LOG(LogTemp, Warning, TEXT("Screen Location of crosshair: %s"), *ScreenLocation.ToString());

	//deproject crosshair to 3d space or world, with direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player camera LookDirection is pointed at: %s"), *LookDirection.ToString());
		//line trace through the crosshair in the direction of deprojection, called LookDirection
		GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}
	return true; //initialization for testing
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	//deproject crosshair to 3d space or world, with direction
	FVector CameraWorldLocation; // have to create these variables, needed for the deproject function
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, //Screenlocation is a FVector2D, so it returns multiple things
		ScreenLocation.Y, //Screenlocation is a FVector2D, so it returns multiple things
		CameraWorldLocation, //we apparently don't care about this atm
		LookDirection); //this is a reference. seems to be relevant when "delegated" to a function.
		//I guess we don't have to define the signature or function of this one. probably because it's already part of Unreal. It is a boolean.
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &OutHitLocation, FVector LookDirection) const
{
	FHitResult HitResult; //this will be the variable that stores the FHitResult from LineTraceSingleByChannel
	auto StartLocation = PlayerCameraManager->GetCameraLocation(); //variable storing location of player camera
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange); //interpretted as starting at a location, getting a direction
			//and multiplying the direction by the LineTraceRange defined in the header.
	if(GetWorld()->LineTraceSingleByChannel( //since all the parameters have been DEFINED, we don't need "relative" code here,
			//so GetWorld can be used.
		HitResult, //defined above
		StartLocation, //defined above
		EndLocation, //defined above, this is the only one which uses a variable from another function
		ECollisionChannel::ECC_Visibility)
	)
	{
		OutHitLocation = HitResult.Location; //this converts the FHitResult to a vector which will be used for &OutHitLocation
			//set OutHitLocation to that vector result so it prints properly in the log.
		return true;
	}
	else 
	{ 
		OutHitLocation = FVector(0);
		return false; 
	}
}
