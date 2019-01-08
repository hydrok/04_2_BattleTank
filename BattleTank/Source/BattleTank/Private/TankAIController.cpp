// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() //virtual and void are removed here because they arent needed.
{
	Super::BeginPlay(); //call default behaviour before anything else.
	UE_LOG(LogTemp, Warning, TEXT("TankAIController has initialized")); //this is a logout message useful for debugging.
	auto AIControlledTank = GetAIControlledTank(); //variable created for logging and debugging purposes, is the function finding a tank?
	if (!AIControlledTank) //if nothing returned from ControlledTank function
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController has not possessed a Tank")); //make a log.
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController is possessing %s"), *(AIControlledTank->GetName())); //log the tank that is possessed.
		// the *AIControlledTank->GetName() means call the GetName function (which comes from a parent class) from the actior that was retruned
		//from the AIControlledTank = GetAIControlledTank() which is also Cast<ATank>(GetAIControlledTank())
	}

}

ATank* ATankAIController::GetAIControlledTank() const
//this is a "getter". Get value pointed to by GetControlledTank() of type ATank.
// the ATankAIController:: part makes the reference specificically from ATankAIController.h, I think...
{
	//The TankAIController needs to know what tank it is controlling.
	return Cast<ATank>(GetPawn()); //this CAST syntax asks to run GetPawn() from ATank...I think...

}


