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

ATank* ATankPlayerController::GetControlledTank() const 
//this is a "getter". Get value pointed to by GetControlledTank() of type ATank.
// the ATankPlayerController:: part makes the reference specificically from TankPlayerController.h, I think...
{
	//The TankPlayerController needs to know what tank it is controlling.
	return Cast<ATank>(GetPawn()); //this CAST syntax asks to run GetPawn() from ATank...I think...

}