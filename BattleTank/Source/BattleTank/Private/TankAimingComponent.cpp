// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h" //need to include this so the aiming component is aware of the barrel functions
#include "TankTurret.h" //need to include this so the aiming component is aware of the turret functions
#include "ConstructorHelpers.h" //to deal with unreal bug
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
		//this is to fix the blueprint selection bug in unreal.
	static ConstructorHelpers::FClassFinder<AProjectile> Proj(TEXT("/Game/Tank/Projectile_BP"));
	if (Proj.Class)
	{
		ProjectileBlueprint = Proj.Class;
	}

	PrimaryComponentTick.bCanEverTick = true; 
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds(); //update the last fire time.
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) < ReloadTimeinSeconds) //reload logic
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else 
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector OutHitLocation) //has LaunchSpeed.
{
	auto OurTankName = GetOwner()->GetName(); //gets object name of the owner class (tank in this case)
	auto BarrelLocation = Barrel->GetComponentLocation();
	auto TurretLocation = Turret->GetComponentLocation();
	
		//it seems that whenever the AimAt is called that the OutHitLocation is populated in that AimAt call, then reported here.
	if (!ensure(Barrel))
	{
		return;
	}
	FVector OutLaunchVelocity(0); //out parameter
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); //this is at the end of the barrel. The socket is created by user in UE4
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(   //it seems that when booleans are involved, do an if, since calling them alone is annoying
		this, //TankAimingComponent is sufficient as a world context...what does that mean?
		OutLaunchVelocity, //out parameter
		StartLocation, //location near end of barrel
		OutHitLocation, //location of tank aim
		LaunchSpeed, //as defined in tank.h
		false, //boolean for high arc. true means favour high arc
		0, //must be a collision radius
		0, //gravity. 0 means no override
		ESuggestProjVelocityTraceOption::DoNotTrace //trace or no?
		);
	if(bHaveAimSolution&&(OutHitLocation!=FVector(0)))
	{		
		AimDirection = OutLaunchVelocity.GetSafeNormal(); //this converts the LaunchVelocity Length to the LaunchDirectionLength, a unit vector
		auto Time = GetWorld()->GetTimeSeconds(); //for timestamps
		MoveBarrelTowards(AimDirection);
		//MoveTurretTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("TIME: %f. %s AimDirection is %s aiming at %s from location of Barrel: %s with LaunchSpeed %f."), 
			//Time, *OurTankName, *AimDirection.ToString(), *OutHitLocation.ToString(), *BarrelLocation.ToString(), LaunchSpeed); 
			//The OutHitLocation.ToString() is just like other variables	
		//UE_LOG(LogTemp, Warning, TEXT("TIME: %f. AimSolution Found!"), Time)
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds(); //for timestamps
		//UE_LOG(LogTemp, Warning, TEXT("TIME: %f. No AimSolution found"), Time)
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	//if we have an aim solution
	//calculate difference between current barrel elevation and Aim Direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //rotation is a struct that contains roll pitch yaw.
		//this is the current roll pitch yaw of the barrel at the moment
	auto AimAsRotator = AimDirection.Rotation();  //the is the rotation the barrel has to go to.
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator %s"), *AimAsRotator.ToString()); //The OutHitLocation.ToString() is just like other variables
	auto DeltaRotator = AimAsRotator - BarrelRotator; //this calculates the difference between what we need and what we have

	Barrel->ElevateBarrel(DeltaRotator.Pitch); //call ElevatePitch from TankBarrel. It will set relative barrel rotation
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
	else
	{
		Turret->RotateTurret(-DeltaRotator.Yaw); //yaw the shortest way.
	}
		//and it will feed DelatRotator as the RelativeSpeed, which will be clamped to be -1 and 1
		//this is a way to pass positive or negative value based on degree rotation.
}

//void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
//{
//	if (!ensure(Barrel) || !ensure(Turret)) { return; }
//	auto TurretRotator = Turret->GetForwardVector().Rotation();
//	auto AimAsRotator = AimDirection.Rotation();
//	auto TurretDeltaRotator = AimAsRotator - TurretRotator;
//	Turret->RotateTurret(TurretDeltaRotator.Yaw);
//}

void UTankAimingComponent::Initialise(UTankBarrel*BarrelToSet, UTankTurret*TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire()
{
	

	if (FiringState !=EFiringState::Reloading)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

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

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}