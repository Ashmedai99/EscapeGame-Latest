
#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT

UOpenDoor::UOpenDoor()
{

	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;
	
	if (!TriggerVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no pressureplate set!"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() > MassToOpenDoor)
	{
		
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
		
	}
	else
	{
		if (DoorCloseDelay < GetWorld()->GetTimeSeconds() - DoorLastOpened) {
			CloseDoor(DeltaTime);
			}
	}

}
void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if (!TriggerVolume) { return TotalMass; }
	TriggerVolume->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor -> FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}
