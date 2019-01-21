// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //this was changed from true
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));
		//this was removed because we chose to do movement component a lslightly different way than aimingcomponent.

	//this is creating a sub-object from UTankAimingComponent, it needs an FName. this adds an AimingComponent to the Tank_BP windows in UE4
	//The Tank_BP inherits the AimingComponent.
}

//void ATank::SetBarrelReference(UTankBarrel *BarrelToSet)
//{
//	TankAimingComponent->SetBarrelReference(BarrelToSet); //This was defined in the TankAimingComponent. This line delgates the 
//			//set barrel reference (barrel to set) to the AimingComponent
//			//check the event graph of the Tank_BP to see that the references exist there and the relationship that was made.
//	Barrel = BarrelToSet; //keeping a local reference to the Barrel. this is for the projectile spawn
//}
//
//void ATank::SetTurretReference(UTankTurret *TurretToSet)
//{
//	TankAimingComponent->SetTurretReference(TurretToSet); //This was defined in the TankAimingComponent. This line delgates the 
//			//set turret reference (barrel to set) to the AimingComponent
//			//check the event graph of the Tank_BP to see that the references exist there and the relationship that was made.
//}

//Removed in lecture 176

//void ATank::IntendMoveForward(float Throw)
//{
//	TankMovementComponent->IntendMoveForward(Throw); //remember that this is a pointer. Launchspeed was added ad-hoc
//}