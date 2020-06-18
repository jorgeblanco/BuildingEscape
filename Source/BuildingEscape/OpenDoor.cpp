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

	OriginalRotation = GetOwner()->GetActorRotation();
	TargetRotation = GetOwner()->GetActorRotation();
	TargetRotation.Add(0.f, TargetYaw, 0.f);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsOpen)
	{
		FRotator CurrentRotation = GetOwner()->GetActorRotation();
		CurrentRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, OpeningSpeed);
		GetOwner()->SetActorRotation(CurrentRotation);

		if (CurrentRotation.Equals(TargetRotation, 1.0f))
		{
			bIsOpen = true;
		}
	}
	
	if (bIsOpen)
	{
		FRotator CurrentRotation = GetOwner()->GetActorRotation();
		CurrentRotation = FMath::RInterpTo(CurrentRotation, OriginalRotation, DeltaTime, OpeningSpeed);
		GetOwner()->SetActorRotation(CurrentRotation);

		if (CurrentRotation.Equals(OriginalRotation, 1.0f))
		{
			bIsOpen = false;
		}
	}
}

