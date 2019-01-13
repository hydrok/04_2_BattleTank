// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	//I think a default sub object just allows the defined object (ProjectileMovement) to appear on a list to be added as a component.
	//the objective here is taht we want it in the Projectile_BP
	ProjectileMovement->bAutoActivate = false; //doesnt satrt flying off until we fire it, we are explicitly setting this
		//worht noting that this can be done entirely in blueprint as well
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float ProjectileSpeed)
	{
	UE_LOG(LogTemp, Warning, TEXT("projectile successfully called"))
		
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * ProjectileSpeed);
	ProjectileMovement->Activate();
	}