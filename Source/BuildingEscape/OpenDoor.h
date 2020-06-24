// Copyright Jorge Blanco 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void LerpDoorOpen(float DeltaTime);
	void LerpDoorClosed(float DeltaTime);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.f;
	
	UPROPERTY(EditAnywhere)
	float OpeningSpeed = 1.0f;
	
	UPROPERTY(EditAnywhere)
	float ClosingSpeed = 2.0f;
	
	UPROPERTY(EditAnywhere)
	float CloseDelayInSeconds = 2.0f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* PressureActivator;
	
	FRotator OriginalRotation;
	FRotator TargetRotation;
	bool bIsOpen = false;
	float DoorCloseTime = 0.f;

		
};
