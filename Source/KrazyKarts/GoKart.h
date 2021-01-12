// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

UCLASS()
class KRAZYKARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:

#pragma region Constructor
	
	// Sets default values for this pawn's properties
	AGoKart();

#pragma endregion

protected:

#pragma region Begin Play Function

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma endregion
	

public:	

#pragma region Tick Function

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ApplyRotation(float DeltaTime);

#pragma endregion
	
#pragma region Input Functions

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion

private:

#pragma region Physics Variables

	// Mass of the car (Kg)
	UPROPERTY(EditAnywhere, Category = "Physics")
	float Mass = 1000;

	// The force applied to the car when the throttle is fully down (N)
	UPROPERTY(EditAnywhere, Category = "Physics")
	float MaxDrivingForce = 10000;

	// The number of degrees rotated per second at full control throw (degree/s)
	UPROPERTY(EditAnywhere, Category = "Physics")
	float MaxDegreesPerSecond;

	// Higher means more drag
	UPROPERTY(EditAnywhere, Category = "Physics")
	float DragCoefficient;

	UPROPERTY(EditAnywhere, Category = "Physics")
	class UBoxComponent* Collider;

#pragma endregion	

#pragma region Movement Variables


	void MoveForward(float Value);

	void MoveRight(float Value);

	FVector Velocity;

	float Throttle;

	float SteeringThrow;


#pragma endregion	

#pragma region Physics Functions

	FVector GetResistance();

#pragma endregion

#pragma region Movement Functions

	void UpdateLocationFromVelocity(float DeltaTime);

#pragma endregion

};
