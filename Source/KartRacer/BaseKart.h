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

	

	// Variables to be changed in editor

	// How long the kart's suspension is
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adjustables")
		float m_SuspensionLength;

	// How strong gravity is
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
		float m_GravityStrength;

	// Modifier for how much control you have turning inwards during a drift
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_InnerDriftControlModifier;

	// Modifier for how much control you have turning outward during a drift
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_OuterDriftControlModifier;

	// How much the kart naturally turns during a drift
	// degrees / second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_AutomaticDriftRotation;

	// your turning capability during a drift before other modifiers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_OverallDriftControllModifier;

	// how fast you can go and still turn at maximum potential
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_MaxSpeedForMaxTurnRadius;

	// Max speed which the kart can travel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_MaxSpeed;

	// the tightest turn radius the kart can perform
	// this turn radius is used below m_MaxSpeedForMaxTurnRadius
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_MinTurnRadius;

	// the largest turn radius your kart can perform
	// basically your stearing at max speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_MaxTurnRadius;

	// how fast the kart accelerates 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_AccelerationForce;

	// how fast the kart reverses
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_ReverseForce;

	// force used for stopping the kart
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_BreakForce;

	// force used to make the kart hop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_HopPower;

	// How long it takes to charge a mini boost during a drift
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_MiniDriftBoostChargeTime;
	
	// How long it takes to charge a mega boost during a drift
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_MegaDriftBoostChargeTime;

	// How much power a mini drift boost provides
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_MiniDriftBoostForce;

	// How much power a mega boost provides
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_MegaDriftBoostForce;

	// The minimum speed at which a kart can drift
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_MinDriftSpeed;

	// when a drift begins your karts velocity direction is rotated to match the drift direction
	// this is how much it's rotated by
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_OnDriftVelocityRotationInDegrees;

	// when in the air the kart interpolates its rotation so it can land correctly
	// this is the speed at which it does that
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_AirRInterpSpeed;

	// when the kart is grounded this controls how fast the kart will interpolate its rotation to match the wheels
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_GroundRInterpSpeed;
	
	// How much resistance the kart has to sliding sideways
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_SlideResistance;

	// How much slower the kart will travel per wheel off the road
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		float m_OffRoadSlowDownPerWheel;

	// Can you drive?
	// true = yes
	// false = no
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		bool m_ControlsEnabled;

	// When a trick is performed a boost is provided instantly
	// this is how much force that boost provides
	UPROPERTY(BlueprintReadWrite, Category = "Trick")
		float m_TrickForceAir;
	
	// Tricks provide a boost when landing
	// This is how much force that boost provides
	UPROPERTY(BlueprintReadWrite, Category = "Trick")
		float m_TrickForceLanded;

	// When hopping to perform a drift the player must push either left or right to control the drift direction
	// They must push further than the dead zone 0-1
	UPROPERTY(BlueprintReadWrite, Category = "Trick")
		float m_DeadZone;

	// blueprint callable functions
	UFUNCTION(BlueprintCallable, Category = "Forces")
		void ApplyForwardForce(float Force);

	UFUNCTION(BlueprintCallable, Category = "Forces")
		void ApplyForce(FVector Force);

	UFUNCTION(BlueprintCallable, Category = "Forces")
		void ApplyForwardImpulse(float Force);

	UFUNCTION(BlueprintCallable, Category = "Forces")
		void ApplyImpulse(FVector Force);

	UFUNCTION(BluePrintNativeEvent)
		void SpawnTrickEmitter();
		virtual void SpawnTrickEmitter_Implementation();

	UFUNCTION(BluePrintNativeEvent)
		void SpawnPoofEmitter();
		virtual void SpawnPoofEmitter_Implementation();

	
private:

	// components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CollisionMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BodyMesh;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UArrowComponent*> Arrows;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UStaticMeshComponent*> Wheels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* FrontRightArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* FrontLeftArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* BackRightArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* BackLeftArrow;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FrontRightWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FrontLeftWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BackRightWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BackLeftWheel;

	// Used to ignore rotations generated by unreal
	FRotator		m_RotationToBeMaintained;

	float			m_WheelRadius;
	float			m_DriftTimer;

	int32			m_GroundedWheelsLastFrame;
	int32			m_GroundedWheels;
	int32			m_WheelsOffRoad;
	int32			m_DriftDirection;

	FVector			m_GravityDirection;
	FVector			m_LocationLastFrame;
	FVector			m_ForwardVectorFromWheels;
	FVector			m_RightVectorFromWheels;

	bool			m_Drifting;
	bool			m_CanTrick;
	bool			m_DriftButtonHeld;
	bool			m_DriftReady;
	bool			m_HasTrickBoost;
	bool			m_InTrickVolume;
	

	FTimerHandle	m_CameraLagTimerHandle;
	/* Sets the rotation to RotatationToBeMaintained. 
	This is done to avoid rotations generated by Unreal */
	void ResetRotation();
	FVector GetGravityDirection();
	void UpdateSuspension();
	void CalculatebodyRotation();
	void CheckIfLanded();
	void Landed();
	void DealWithGravity();
	void EndDrift();
	void LandedInDrift();
	void EnableCameraLag();
	void SetForwardVectorFromWheels();
	void SetRightVectorFromWheels();
	void RotationInterpolation(float DeltaTime);
	void DriftPhysics(float DeltaTime);
	void SetLinearDamping();
	// Network Functions
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerRPCSendTurnAxis(float TurnAxis);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastRPCTurnAxis(float TurnAxis);

	UFUNCTION(Server, WithValidation, Reliable)
		void ServerRPCSendGasBreak(float GasAxis);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastRPCGasBreak(float GasAxis);

	// Input functions
	void ApplyGasBreak(float AxisValue);
	void Turn(float AxisValue);
	void LookBackPressed();
	void LookBackReleased();
	void HopPressed();
	void HopReleased();
	void UseItem();
	
	void PerformTurning(float AxisValue);
	void PerformGasBreak(float AxisValue);

	//checks
	bool IsGrounded();
};
