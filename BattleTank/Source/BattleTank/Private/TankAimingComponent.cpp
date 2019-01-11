// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed) //has LaunchSpeed.
{
	auto OurTankName = GetOwner()->GetName(); //gets object name of the owner class (tank in this case)
	auto BarrelLocation = Barrel->GetComponentLocation();
	
		//it seems that whenever the AimAt is called that the OutHitLocation is populated in that AimAt call, then reported here.

	if (!Barrel)
	{
		return;
	}
	FVector OutLaunchVelocity; //out parameter
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); //this is at the end of the barrel. The socket is created by user in UE4

	if (UGameplayStatics::SuggestProjectileVelocity(   //it seems that when booleans are involved, do an if, since calling them alone is annoying
			this, //TankAimingComponent is sufficient as a world context...what does that mean?
			OutLaunchVelocity, //out parameter
			StartLocation, //location near end of barrel
			OutHitLocation, //location of tank aim
			LaunchSpeed, //as defined in tank.h
			false, //boolean for high arc. true means favour high arc
			0, //must be a collision radius
			0, //gravity. 0 means no override
			ESuggestProjVelocityTraceOption::DoNotTrace //trace or no?
		)
	)
	{		
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //this converts the LaunchVelocity Length to the LaunchDirectionLength, a unit vector
		UE_LOG(LogTemp, Warning, TEXT("%s AimDirection is %s aiming at %s from location of Barrel: %s with LaunchSpeed %f"),  *OurTankName, *AimDirection.ToString(), *OutHitLocation.ToString(), *BarrelLocation.ToString(), LaunchSpeed); //The OutHitLocation.ToString() is just like other variables
	}
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent *BarrelToSet)
{
	
	Barrel = BarrelToSet; //AKA the barrel to set is the barrel.
}