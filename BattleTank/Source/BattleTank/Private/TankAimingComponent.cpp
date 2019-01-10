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

void UTankAimingComponent::AimAt(FVector OutHitLocation)
{
	auto OurTankName = GetOwner()->GetName(); //gets object name of the owner class (tank in this case)
	UE_LOG(LogTemp, Warning, TEXT("%s is AimAt %s"), *OurTankName, *OutHitLocation.ToString()); //The OutHitLocation.ToString() is just like other variables
		//it seems that whenever the AimAt is called that the OutHitLocation is populated in that AimAt call, then reported here.
}