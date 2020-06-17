// Copyright Jorge Blanco 2020


#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	const float TargetRotation = 90.f;
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Add(0.f, TargetRotation, 0.f);
	GetOwner()->SetActorRotation(CurrentRotation);
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

