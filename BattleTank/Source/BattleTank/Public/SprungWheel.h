// Copyright HardieSoftworks

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

private:
	void SetupConstraint();

	UPROPERTY(VisibleAnywhere, Category = "Spring Setup")
	UPhysicsConstraintComponent * PhysicsConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Spring Setup")
		UStaticMeshComponent * Axle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Spring Setup")
		UPhysicsConstraintComponent * AxleWheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Spring Setup")
	UStaticMeshComponent * Wheel = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

	float TotalForceMagnitudeThisFrame = 0;

};
