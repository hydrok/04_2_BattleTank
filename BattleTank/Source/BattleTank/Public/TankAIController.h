// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	//ATank* GetAIControlledTank() const; //this is a "getter". Get value pointed to by GetAIControlledTank() of type ATank.
	//this was defactored
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override; //this checks to make sure that BeginPlay exists somehwere up the hierarchy of classes.
	//in this case it is the AActor that has it. The virtual is defined in AActor as well, and it allows any child to extend the
	//functionality of BeginPlay()
	
	//ATank *GetPlayerTank() const; // this is a pointer to the player tank, the AI needs to recognize the playercontrolled tank.
	//return the value pointed to by GetPlayerTank of type ATank.
	//this was defactored

	//void AimTowardsPlayer(); //defactored

	virtual void SetPawn(APawn * InPawn) override; //this gets called when the pawn is possessed.

	UFUNCTION()
		void OnPossessedTankDeath();

protected:
	UPROPERTY(EditDefaultsOnly,Category = "Setup")
		float AcceptanceRadius = 8000; //how close the AI gets to the player before stopping. 3 meters to start.
};
