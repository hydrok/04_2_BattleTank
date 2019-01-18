// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declaration makes the tank aware of the tank barrel class.
class UTankBarrel;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector OutHitLocation); //the aim functionality, used by both the PlayerController and the AIController
		//does not require LaunchSpeed

	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category=Setup)
	void SetBarrelReference(UTankBarrel *BarrelToSet); //this is going to make a method that we can call from blueprint.

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret *TurretToSet); //this is going to make a method that we can call from blueprint.

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire(); //this is going to make a method that we can call from blueprint.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = Input)
	UTankAimingComponent *TankAimingComponent = nullptr; //a pointer to UTankAimingComponent called TankAiming Component

	UPROPERTY(BlueprintReadOnly, Category = Input)
	UTankMovementComponent *TankMovementComponent = nullptr;

private:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing) //creating a launch speed float variable that appears in the UE4 editor
		float LaunchSpeed = 4000; // it has been set up to be overwritable in blueprint.

	UPROPERTY(EditDefaultsOnly, Category = Firing) //EditDefaultsOnly lets you ONLY modify the archetype, 
			//and not each instance of "Tank". can only edit it the BLUEPRINT
	float ReloadTimeinSeconds = 3;

	double LastFireTime = 0;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup) // TODO may want to revert this to EditAnywhere if different BP projectiles based
			//on tank class, example: you are allowed to choose a different tank.
		TSubclassOf<AProjectile> ProjectileBlueprint; //reference to the blueprint in C++. Allows designer to select which blueprint 
			//can be used for the projectile blueprint. A pointer to ANY UClass TSublcass restricts to only classes in the <>

	UTankBarrel * Barrel = nullptr; //Local Barrel Reference for spawning projectile. something similar was done 
		//for AimingComponent but we need a local one here


};
