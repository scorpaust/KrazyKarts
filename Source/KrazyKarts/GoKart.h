// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKartMovementComponent.h"
#include "GoKartMovementReplicator.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UGoKartMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UGoKartMovementReplicator* MovementReplicator;


#pragma region Tick Function

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma endregion
	
#pragma region Input Functions

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion

private:

#pragma region Components

	
	UPROPERTY(EditAnywhere, Category = "Physics")
	class UBoxComponent* Collider;

#pragma endregion	



#pragma region Movement Functions


	void MoveForward(float Value);

	void MoveRight(float Value);

	

#pragma endregion

};
