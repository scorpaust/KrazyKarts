// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

#pragma region Structs

USTRUCT()
struct FGoKartMove {

	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		float Throttle;

	UPROPERTY()
		float SteeringThrow;

	UPROPERTY()
		float DeltaTime;

	UPROPERTY()
		float Time;
};

USTRUCT()
struct FGoKartState {

	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		FVector Velocity;

	UPROPERTY()
		FGoKartMove LastMove;

	UPROPERTY()
		FTransform Transform;

};

#pragma endregion


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

#pragma region Game State Variables

	AGameStateBase* GameState;

#pragma endregion

#pragma region Tick Function

	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

	// The minimum radius of the car turning circle at full lock (m)
	UPROPERTY(EditAnywhere, Category = "Physics")
	float MinTurningRadius;

	// Higher means more drag
	UPROPERTY(EditAnywhere, Category = "Physics")
	float DragCoefficient;

	// Higher means more rolling resistance
	UPROPERTY(EditAnywhere, Category = "Physics")
	float RollingResistanceCoefficient;

	UPROPERTY(EditAnywhere, Category = "Physics")
	class UBoxComponent* Collider;

#pragma endregion	

#pragma region Movement Variables

	UPROPERTY(Replicated)
	FVector Velocity;

	float Throttle;

	float SteeringThrow;

	TArray<FGoKartMove> UnaknowledgeMoves;


#pragma endregion	

#pragma region Network Variables

	UPROPERTY(ReplicatedUsing = OnRep_ServerState)
	FGoKartState ServerState;

#pragma endregion

#pragma region Network Functions

	UFUNCTION()
	void OnRep_ServerState();

#pragma endregion

#pragma region Physics Functions

	FVector GetAirResistance();

	FVector GetRollingResistance();

#pragma endregion

#pragma region Movement Functions

	void SimulateMove(FGoKartMove Move);

	FGoKartMove CreateMove(float DeltaTime);

	void ClearAknowledgeMoves(FGoKartMove LastMove);

	void MoveForward(float Value);

	void MoveRight(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SendMove(FGoKartMove Move);

	void ApplyRotation(float DeltaTime, float SteeringThrow);

	void UpdateLocationFromVelocity(float DeltaTime);

#pragma endregion

};
