// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float DegreePerSecond)
{
	//rotate turret to aim direction in z for one frame (this frame)
	UE_LOG(LogTemp, Warning, TEXT("Barrel is elevating at speed %f"), DegreePerSecond);
}