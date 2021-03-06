// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankPlayerController::SetPawn(APawn * InPawn) //this gets called when the pawn is possessed.
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		//subscribe to ondeath method broadcast
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::BeginPlay() //virtual and void are removed here because they arent needed.
{
	Super::BeginPlay(); //call default behaviour before anything else.

	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController can't find component at BeginPlay"))
	}

	UE_LOG(LogTemp, Warning, TEXT("PlayerController has initialized")); //this is a logout message useful for debugging.
	auto ControlledTank = GetPawn(); //variable created for logging and debugging purposes, is the function finding a tank?
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

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } //if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		return;
	}
	else
	{
		FVector OutHitLocation; //Out parameter, this is a FVector type variable
		bool bGotHitLocation = GetSightRayHitLocation(OutHitLocation);
		if (bGotHitLocation) //this will eventually ray-trace as well, which we neeeeeeee
		{	
			AimingComponent->AimAt(OutHitLocation); //pass from TankPlayerController to the Tank. The AimAt part is the signal.
				//Call AimAt from the controled tank
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
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location of crosshair: %s"), *ScreenLocation.ToString());

	//deproject crosshair to 3d space or world, with direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Player camera LookDirection is pointed at: %s"), *LookDirection.ToString());
		//line trace through the crosshair in the direction of deprojection, called LookDirection
		return GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}
	else
	{
		return false; 
	}
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
	FCollisionQueryParams Params; //solution suggested by TA for determining crosshair/target validity
	Params.AddIgnoredActor(GetPawn());
	if(GetWorld()->LineTraceSingleByChannel( //since all the parameters have been DEFINED, we don't need "relative" code here,
			//so GetWorld can be used.
		HitResult, //defined above
		StartLocation, //defined above
		EndLocation, //defined above, this is the only one which uses a variable from another function
		ECollisionChannel::ECC_Camera,
		Params)
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
