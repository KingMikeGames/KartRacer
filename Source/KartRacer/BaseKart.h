// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "BaseKart.generated.h"

UCLASS()
class KARTRACER_API ABaseKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseKart();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// components

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* CollisionMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UArrowComponent*> Arrows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UStaticMeshComponent*> Wheels;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* Camera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
		UArrowComponent* FrontRightArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
		UArrowComponent* FrontLeftArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
		UArrowComponent* BackRightArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
		UArrowComponent* BackLeftArrow;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheel")
		UStaticMeshComponent* FrontRightWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheel")
		UStaticMeshComponent* FrontLeftWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheel")
		UStaticMeshComponent* BackRightWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheel")
		UStaticMeshComponent* BackLeftWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adjustables")
		float m_SuspensionLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
		float m_GravityStrength;
private:
	// Used to ignore rotations generated by unreal
	FRotator		m_RotationToBeMaintained;

	float			m_WheelRadius;
	int32			m_GroundedWheelsLastFrame;
	int32			m_GroundedWheels;
	int32			m_WheelsOffRoad;
	FVector			m_GravityDirection;

	/* Sets the rotation to RotatationToBeMaintained. 
	This is done to avoid rotations generated by Unreal */
	void ResetRotation();
	FVector GetGravityDirection();
	void UpdateSuspension();
	void SetBodyHeight(float AverageWheelHeight);
	void CalculatebodyRotation();
	void CheckIfLanded();
	void Landed();
	void DealWithGravity();
	
	// Input functions
	void ApplyGasBreak(float AxisAngle);
	void Turn(float AxisAngle);
	void LookBack();
	void DriftHop();
	void UseItem();

	// Input Function Bindings
	
};
