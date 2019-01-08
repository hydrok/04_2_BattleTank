// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const 
//this is a "getter". Get value pointed to by GetControlledTank() of type ATank.
// the ATankPlayerController:: part makes the reference specificically from TankPlayerController.h, I think...
{
	//The TankPlayerController needs to know what tank it is controlling.
	return Cast<ATank>(GetPawn());
		//the Cast is saying to treat the GetPawn function as if it was coming from the ATank component?
}