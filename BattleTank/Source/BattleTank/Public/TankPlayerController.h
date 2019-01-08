// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const; //this is a "getter". Get value pointed to by GetControlledTank() of type ATank.
	
	virtual void BeginPlay() override; //this checks to make sure that BeginPlay exists somehwere up the hierarchy of classes.
		//in this case it is the AActor that has it. The virtual is defined in AActor as well, and it allows any child to extend the
		//functionality of BeginPlay()

	// Called every frame
	virtual void Tick(float DeltaTime) override; //virtual means that any child can override or enhance this. In this case we also override
		//which enhances the parent function Tick.

private:
	void AimTowardsCrosshair(); //start the tank moving the barrel toward the aiming reticule.
	bool GetSightRayHitLocation(FVector &OutHitLocation) const; //returns boolean: TRUE if a location through reticule is terrain, given a distance.
		//the & part is because it is a pointer saying the address of OutHitLocation which is of type FVector.
		//explanation from course: An out parameter is passed by reference meaning you are passing the memory address of that parameter to the function.
		//this is useful when the out variable has a changing value, especially when in a tick fucntion! Instead of passing a variable straight to
		//the function, the address of the variable is passed and the value is read from the address see the cpp for implementation.
		//so you can pass a variable and the function will automatically know its an address and the value will always be changed at that address.
		//if you pass just a variable, a copy is made and changes to values are made only in the copy variable, not the original.
};
