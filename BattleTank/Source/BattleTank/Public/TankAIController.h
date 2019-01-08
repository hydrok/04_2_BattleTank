// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATank* GetAIControlledTank() const; //this is a "getter". Get value pointed to by GetAIControlledTank() of type ATank.

	virtual void BeginPlay() override; //this checks to make sure that BeginPlay exists somehwere up the hierarchy of classes.
	//in this case it is the AActor that has it. The virtual is defined in AActor as well, and it allows any child to extend the
	//functionality of BeginPlay()
	
	
};
