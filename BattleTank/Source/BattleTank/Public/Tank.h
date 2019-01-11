// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h" //we are delegating aiming to this.
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector OutHitLocation); //the aim functionality, used by both the PlayerController and the AIController
		//does not require LaunchSpeed

	UFUNCTION(BlueprintCallable, Category=Setup)
	void SetBarrelReference(UStaticMeshComponent *BarrelToSet); //this is going to make a method that we can call from blueprint.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent *TankAimingComponent = nullptr; //a pointer to UTankAimingComponent called TankAiming Component


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing) //creating a launch speed float variable that appears in the UE4 editor
		float LaunchSpeed = 100000; // it has been set up to be overwritable in blueprint.
	
};
