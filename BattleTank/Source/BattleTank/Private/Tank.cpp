// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //this was changed from true
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Cow: Tank C++ Construct"), *TankName)

	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));
		//this was removed because we chose to do movement component a lslightly different way than aimingcomponent.

	//this is creating a sub-object from UTankAimingComponent, it needs an FName. this adds an AimingComponent to the Tank_BP windows in UE4
	//The Tank_BP inherits the AimingComponent.
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); //needed for BP to run!!!
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Cow: Tank C++ BeginPlay"), *TankName)

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

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeinSeconds; //reload logic
	if ( isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>( //auto projectile gets us the projectile we need so we can do other stuff with it
			ProjectileBlueprint, //the thing we are going to spawn
			Barrel->GetSocketLocation(FName("Projectile")), //getting the location of the barrel socket into a variable
			Barrel->GetSocketRotation(FName("Projectile")) //getting the rotation of the barrel socket into a variable
			);//spawn a projectile at the socket location/rotation of the barrel.

		Projectile->LaunchProjectile(LaunchSpeed); //call function from Projectile. auto projectile defines this or something.
				//LaunchSpeed already defined.
		LastFireTime = FPlatformTime::Seconds(); //update the last fire time.
	}
}

//void ATank::IntendMoveForward(float Throw)
//{
//	TankMovementComponent->IntendMoveForward(Throw); //remember that this is a pointer. Launchspeed was added ad-hoc
//}