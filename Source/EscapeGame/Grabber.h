#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPEGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:

	UGrabber();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void FindPhysicsHandle();
	void SetupInputComponnent();
	void Grab();
	void Released();

	FHitResult GetFirstPlayerHit() const;

protected:

private:
	float Reach = 250.f;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;

	FVector GetPlayerReach() const;
	FVector GetPlayerWorldPos() const;
};
