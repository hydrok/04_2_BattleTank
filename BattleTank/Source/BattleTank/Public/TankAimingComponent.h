// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h" //had to add this for the barrel location.
#include "Kismet/GameplayStatics.h" //for projectile velocity suggestion
#include "TankAimingComponent.generated.h"

//forward declaration makes the aiming component aware of the tank barrel class.
class UTankBarrel;
class UTankTurret;
//Hold barrel properties and Elevate Method

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector OutHitLocation, float LaunchSpeed);
	
	void SetBarrelReference(UTankBarrel *BarrelToSet); //this is a setter. A pointer to static mesh component
	void SetTurretReference(UTankTurret *TurretToSet);


private:
	UTankBarrel *Barrel = nullptr; //this is a pointer to the barrel meshcomponent of the Tank_BP
		//the pointer now points to UTankBarrel, which we just created.
	UTankTurret *Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
	
};
