// Copyright Jorge Blanco 2020


#include "Grabber.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	SetUpPhysicsHandle();
	SetUpInput();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached, move the object we're holding
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachVector());
	}
}

void UGrabber::SetUpPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("No physics handle component found. Did you forget to add one to %s?"),
			*GetOwner()->GetName()
		);
	}
}

void UGrabber::SetUpInput()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("No input component found. Did you forget to add one to %s?"),
			*GetOwner()->GetName()
		);
	}
}

FHitResult UGrabber::RayCastForPhysicBodies() const
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	
	// Get player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	// Ray cast out to reach
	const FVector RayCastEnd = GetReachVector();
	// DrawDebugLine(
	// 	GetWorld(),
	// 	PlayerLocation,
	// 	RayCastEnd,
	// 	FColor(255, 0, 0),
	// 	false,
	// 	0,
	// 	0,
	// 	5.f
	// );

	FHitResult Hit;
	
	// Collision params to use player collision (simple) and ignore the player pawn
	FCollisionQueryParams Params(TEXT(""), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerLocation,
		RayCastEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		Params
	);

	// See if it hits
	// AActor* ActorHit = Hit.GetActor();
	// if (ActorHit)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *ActorHit->GetName());
	// }

	return Hit;
}

FVector UGrabber::GetReachVector() const
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	return PlayerLocation + PlayerRotation.Vector() * PlayerReach;
}

void UGrabber::Grab()
{
	const FHitResult Hit = RayCastForPhysicBodies();
	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();
	if (ComponentToGrab && PhysicsHandle)
	{
		const FVector ReachVector = GetReachVector();
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			ReachVector
		);
	}
}

void UGrabber::Release()
{
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

