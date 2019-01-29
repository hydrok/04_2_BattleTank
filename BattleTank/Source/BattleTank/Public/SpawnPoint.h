// Copyright HardieSoftworks

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup") // TODO may want to revert this to EditAnywhere if different BP projectiles based
		//on tank class, example: you are allowed to choose a different tank.
		TSubclassOf<AActor>SpawnClass; //reference to the blueprint in C++. Allows designer to select which blueprint 

};
