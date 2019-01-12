// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


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

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) //if nothing returned from GetPlayerTank function
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController has not found a player")); //make a log.
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController has found a player possessing %s"), *(PlayerTank->GetName())); //log the tank that is possessed.
	}

}

void ATankAIController::Tick(float DeltaTime) //standard tick
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer(); //aim towards player, if one exists, see function
}

void ATankAIController::AimTowardsPlayer()
{
	if (!GetPlayerTank()) //only activate aiming routine if a player exists
	{
		return;
	}
	else
	{
		GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation()); 
		//call the AimAt functionality from the Tank, and have it at aim at the Player Location
	}
}

ATank* ATankAIController::GetAIControlledTank() const
//this is a "getter". Get value pointed to by GetControlledTank() of type ATank.
// the ATankAIController:: part makes the reference specificically from ATankAIController.h, I think...
{
	//The TankAIController needs to know what tank it is controlling.
	return Cast<ATank>(GetPawn()); //this CAST syntax asks to run GetPawn() from ATank...I think...

}

ATank * ATankAIController::GetPlayerTank() const
{
	//get the tank possessed by the player and log out the unique pawn name.
	auto PlayerControlledTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerControlledTank)
	{
		return nullptr; //if no pointer is returned, return nullptr
	}
	else
	{
		return Cast<ATank>(PlayerControlledTank); //cast PlayerControlledTank function to ATank, but only if a player controlled tank was found.
		//syntax could probably also look like this:
		// return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}
}
