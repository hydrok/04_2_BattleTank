// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h" //we are delegating aiming to this.


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //this was changed from true
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));

	//this is creating a sub-object from UTankAimingComponent, it needs an FName. this adds an AimingComponent to the Tank_BP windows in UE4
	//The Tank_BP inherits the AimingComponent.
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector OutHitLocation)
{
	TankAimingComponent->AimAt(OutHitLocation, LaunchSpeed); //remember that this is a pointer. Launchspeed was added ad-hoc
		//ok this is a mindfuck...
		//from outside of the tank, its ok to say "just aim at this thing (OutHitLocation)
		//but from the inside of the tank, there is a notion of LaunchSpeed, and that gets sent to the AimingComponent.
		//So because we are looking at TankAimingComponent, we have to pass another variable, LaunchSpeed, in order to compile.
}

void ATank::SetBarrelReference(UTankBarrel *BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet); //This was defined in the TankAimingComponent. This line delgates the 
			//set barrel reference (barrel to set) to the AimingComponent
			//check the event graph of the Tank_BP to see that the references exist there and the relationship that was made.
	Barrel = BarrelToSet; //keeping a local reference to the Barrel. this is for the projectile spawn
}

void ATank::SetTurretReference(UTankTurret *TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet); //This was defined in the TankAimingComponent. This line delgates the 
			//set turret reference (barrel to set) to the AimingComponent
			//check the event graph of the Tank_BP to see that the references exist there and the relationship that was made.
}

void ATank::Fire()
{
	
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeinSeconds; //reload logic
	if (Barrel && isReloaded)
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

void ATank::IntendMoveForward(float Throw)
{
	TankMovementComponent->IntendMoveForward(Throw); //remember that this is a pointer. Launchspeed was added ad-hoc
}