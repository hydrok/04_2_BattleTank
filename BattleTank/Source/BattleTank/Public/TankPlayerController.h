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

};
