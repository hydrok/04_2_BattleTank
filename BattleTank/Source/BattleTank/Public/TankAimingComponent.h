// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h" //had to add this for the barrel location.
#include "Kismet/GameplayStatics.h" //for projectile velocity suggestion
#include "TankAimingComponent.generated.h"

// Enum for aiming state. Enums are useful when you have category "states"
UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
}; //for the reticule colour

//forward declaration makes the aiming component aware of the tank barrel class.
class UTankBarrel;
class UTankTurret;
//Hold barrel properties and Elevate Method
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringState FiringState = EFiringState::Reloading; //initial value.


public:	
	// Called every frame
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel*BarrelToSet, UTankTurret*TurretToSet);

	void AimAt(FVector OutHitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire(); //this is going to make a method that we can call from blueprint.

	//need method to return firing state for AI
	EFiringState GetFiringState() const; //this is just a getter, notice how there is no void here

	UFUNCTION(BlueprintCallable, Category = "Firing")
		int32 GetRoundsLeft() const;
	
private:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void MoveBarrelTowards(FVector AimDirection);
	//void MoveTurretTowards(FVector AimDirection);

	bool IsBarrelMoving();
	
	UTankBarrel *Barrel = nullptr; //this is a pointer to the barrel meshcomponent of the Tank_BP
		//the pointer now points to UTankBarrel, which we just created.
	UTankTurret *Turret = nullptr;

	// Sets default values for this component's properties
	UTankAimingComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Firing") //creating a launch speed float variable that appears in the UE4 editor
		float LaunchSpeed = 6000; // it has been set up to be overwritable in blueprint.

	UPROPERTY(EditDefaultsOnly, Category = "Firing") //EditDefaultsOnly lets you ONLY modify the archetype, 
			//and not each instance of "Tank". can only edit it the BLUEPRINT
		float ReloadTimeinSeconds = 2;

	double LastFireTime = 0;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Setup") // TODO may want to revert this to EditAnywhere if different BP projectiles based
			//on tank class, example: you are allowed to choose a different tank.
		TSubclassOf<AProjectile> ProjectileBlueprint; //reference to the blueprint in C++. Allows designer to select which blueprint 
			//can be used for the projectile blueprint. A pointer to ANY UClass TSublcass restricts to only classes in the <>

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 120;
};
