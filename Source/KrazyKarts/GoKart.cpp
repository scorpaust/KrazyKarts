// Fill out your copyright notice in the Description page of Project Settings.


#include "GoKart.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "GoKartMovementComponent.h"
#include "GoKartMovementReplicator.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/GameStateBase.h"

#pragma region Constructor Implementation
// Sets default values
AGoKart::AGoKart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");

	RootComponent = Collider;

	MovementComponent = CreateDefaultSubobject<UGoKartMovementComponent>(TEXT("MovementComponent"));

	MovementReplicator = CreateDefaultSubobject<UGoKartMovementReplicator>(TEXT("MovementReplicator"));
}

#pragma endregion

#pragma region Tick Implementation

// Called every frame
void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma endregion

#pragma region Begin  Play Implementation

// Called when the game starts or when spawned
void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
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

	if (MovementComponent == nullptr) return;

	MovementComponent->SetThrottle(Value);

}

void AGoKart::MoveRight(float Value) {

	if (MovementComponent == nullptr) return;

	MovementComponent->SetSteeringThrow(Value);

}

#pragma endregion

