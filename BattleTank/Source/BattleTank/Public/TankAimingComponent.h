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
	Reloading
}; //for the reticule colour

//forward declaration makes the aiming component aware of the tank barrel class.
class UTankBarrel;
class UTankTurret;
//Hold barrel properties and Elevate Method

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringState FiringState = EFiringState::Aiming; //initial value.

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel*BarrelToSet, UTankTurret*TurretToSet);

	void AimAt(FVector OutHitLocation, float LaunchSpeed);
	
private:
	UTankBarrel *Barrel = nullptr; //this is a pointer to the barrel meshcomponent of the Tank_BP
		//the pointer now points to UTankBarrel, which we just created.
	UTankTurret *Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	//void MoveTurretTowards(FVector AimDirection);

	// Sets default values for this component's properties
	UTankAimingComponent();
};
