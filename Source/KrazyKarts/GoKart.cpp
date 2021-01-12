// Fill out your copyright notice in the Description page of Project Settings.


#include "GoKart.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"

#pragma region Constructor Implementation
// Sets default values
AGoKart::AGoKart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");

	RootComponent = Collider;

	MaxDegreesPerSecond = 90;

	DragCoefficient = 16;

}

#pragma endregion

#pragma region Begin  Play Implementation

// Called when the game starts or when spawned
void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
}

#pragma endregion

#pragma region Tick Implementation

// Called every frame
void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Force = GetActorForwardVector() * MaxDrivingForce * Throttle;

	Force += GetResistance();

	FVector Acceleration = Force / Mass;

	Velocity = Velocity + Acceleration * DeltaTime;

	ApplyRotation(DeltaTime);

	UpdateLocationFromVelocity(DeltaTime);

}

#pragma endregion

#pragma region Input Implementation

// Called to bind functionality to input
void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKart::MoveRight);

}

#pragma endregion

#pragma region Movement

void AGoKart::MoveForward(float Value) {

	Throttle = Value;

}

void AGoKart::MoveRight(float Value) {

	SteeringThrow = Value;

}

void AGoKart::ApplyRotation(float DeltaTime)
{
	float RotationAngle = MaxDegreesPerSecond * DeltaTime * SteeringThrow;

	FQuat RotationDelta(GetActorUpVector(), FMath::DegreesToRadians(RotationAngle));

	Velocity = RotationDelta.RotateVector(Velocity);

	AddActorWorldRotation(RotationDelta);
}

#pragma endregion

#pragma region Physics

void AGoKart::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector Translation = Velocity * 100 * DeltaTime;

	FHitResult Hit;

	AddActorWorldOffset(Translation, true, &Hit);

	if (Hit.IsValidBlockingHit()) {

		Velocity = FVector::ZeroVector;

	}
}

FVector AGoKart::GetResistance() {

	return -Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;

}

#pragma endregion