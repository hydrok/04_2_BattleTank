// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void LaunchProjectile(float ProjectileSpeed);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor*OtherActor, UPrimitiveComponent*OtherComponent,
		FVector NormalImpulse, const FHitResult& Hit);

private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Projectile Setup")
	UStaticMeshComponent * CollisionMesh = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Projectile Setup")
	UParticleSystemComponent * LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Projectile Setup")
		UParticleSystemComponent * ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Projectile Setup")
		URadialForceComponent * ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Setup")
		float DestroyDelay = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Setup")
		float ProjectileDamage = 20.f;

	void DestroyProjectile();
};
