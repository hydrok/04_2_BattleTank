// Copyright HardieSoftworks

#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "SprungWheel.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<ASprungWheel> Proj(TEXT("/Game/Tank/SprungWheel_BP"));
	if (Proj.Class)
	{
		SpawnClass = Proj.Class;
	}
	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	//this code gets the actor that spawned and its location. Then finsihes spawning it. 
	//the code attaches the spawn to an actor (see blueprint for attachment)
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass,GetComponentTransform());
	if (!SpawnedActor) { return; }
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

