// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("This is a warning!"));
	// UE_LOG(LogTemp, Error, TEXT("This is an error"));
	// UE_LOG(LogTemp, Display, TEXT("This is just a message"));

	FString Log = TEXT("Hello!");
	FString* PtrLog = &Log;


	const FString Name = GetOwner()->GetName();
	// const FString ObjectPosition = GetOwner()->GetActorLocation().ToString();
	const FString ObjectPosition = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Display, TEXT("Object %s position: %s"), *Name, *ObjectPosition);

}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
