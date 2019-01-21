// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declaration makes the tank aware of the tank barrel class.

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	ATank();
};
