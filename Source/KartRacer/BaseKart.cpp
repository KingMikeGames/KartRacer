// Fill out your copyright notice in the Description page of Project Settings.

#include "KartRacer.h"
#include "BaseKart.h"

#include "StaticFunctionLibrary.h"

// Sets default values
ABaseKart::ABaseKart() :
	m_WheelRadius(10),
	m_SuspensionLength(30),
	m_GravityStrength(3000),
	m_Drifting(false),
	m_GroundedWheels(0),
	m_GroundedWheelsLastFrame(0),
	m_WheelsOffRoad(0),
	m_GravityDirection(FVector(0, 0, -1)),
	m_OuterDriftControlModifier(0.25f),
	m_InnerDriftControlModifier(1.0f),
	m_AutomaticDriftRotation(30.0f),
	m_OverallDriftControllModifier(40.0f),
	m_MaxSpeedForMaxTurnRadius(1000.0f),
	m_MaxSpeed(4000),
	m_MinTurnRadius(1000),
	m_MaxTurnRadius(4000),
	m_AccelerationForce(2500),
	m_ReverseForce(1250),
	m_BreakForce(2500)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetTickGroup(TG_PostPhysics);
#pragma region ComponentInit
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollisionRoot"));
	RootComponent = CollisionMesh;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	BodyMesh->AttachTo(RootComponent);

#pragma region Arrow Initialization
	FrontRightArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FrontRightArrow"));
	FrontRightArrow->AttachTo(BodyMesh);
	Arrows.Add(FrontRightArrow);

	FrontLeftArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FrontLeftArrow"));
	FrontLeftArrow->AttachTo(BodyMesh);
	Arrows.Add(FrontLeftArrow);

	BackRightArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("BackRightArrow"));
	BackRightArrow->AttachTo(BodyMesh);
	Arrows.Add(BackRightArrow);

	BackLeftArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("BackLeftArrow"));
	BackLeftArrow->AttachTo(BodyMesh);
	Arrows.Add(BackLeftArrow);
#pragma endregion

#pragma region Wheel Initialization
	FrontRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontRightWheel"));
	FrontRightWheel->AttachTo(BodyMesh);
	Wheels.Add(FrontRightWheel);

	FrontLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontLeftWheel"));
	FrontLeftWheel->AttachTo(BodyMesh);
	Wheels.Add(FrontLeftWheel);

	BackRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackRightWheel"));
	BackRightWheel->AttachTo(BodyMesh);
	Wheels.Add(BackRightWheel);

	BackLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackLeftWheel"));
	BackLeftWheel->AttachTo(BodyMesh);
	Wheels.Add(BackLeftWheel);
#pragma endregion

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(BodyMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(CameraBoom);
#pragma endregion

}

// Called when the game starts or when spawned
void ABaseKart::BeginPlay()
{
	Super::BeginPlay();
	
	m_LocationLastFrame = CollisionMesh->GetComponentLocation();
}

// Called every frame
void ABaseKart::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	m_GravityDirection = GetGravityDirection();
	UpdateSuspension();
	ResetRotation();
	CheckIfLanded();
	CalculatebodyRotation();
	DealWithGravity();
	ResetRotation();

}



// Called to bind functionality to input
void ABaseKart::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("Accekerate", this, &ABaseKart::ApplyGasBreak);
	InputComponent->BindAxis("Turn", this, &ABaseKart::Turn);

	InputComponent->BindAction("LookBack", IE_Pressed, this, &ABaseKart::LookBack);
	InputComponent->BindAction("DriftHop", IE_Pressed, this, &ABaseKart::DriftHop);
	InputComponent->BindAction("UseItem", IE_Pressed, this, &ABaseKart::UseItem);
}



void ABaseKart::ApplyForwardForce(float Force)
{
	CollisionMesh->AddForce(CollisionMesh->GetForwardVector() * Force);
}

void ABaseKart::ResetRotation()
{
	CollisionMesh->SetWorldRotation(m_RotationToBeMaintained);
}



FVector ABaseKart::GetGravityDirection()
{
	//TODO: Figure out how to get Gravity volumes
	return FVector(0,0,-1);
}



void ABaseKart::UpdateSuspension()
{
	UWorld* World = GetWorld();
	float AverageHeight = 0;
	m_GroundedWheelsLastFrame = m_GroundedWheels;
	m_GroundedWheels = 0;
	m_WheelsOffRoad = 0;

	for (size_t WheelIndex = 0; WheelIndex < Arrows.Num(); WheelIndex++)
	{
		FHitResult HitData(ForceInit);
		bool hit = UStaticFunctionLibrary::Trace(World, NULL, Arrows[WheelIndex]->GetComponentLocation(), Arrows[WheelIndex]->GetComponentLocation() + Arrows[WheelIndex]->GetForwardVector() * (m_SuspensionLength + m_WheelRadius), HitData, ECC_GameTraceChannel1, true);
		
		if (hit)
		{
			m_GroundedWheels++;
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Hit");

			if (HitData.PhysMaterial->Friction > 1)
			{
				m_WheelsOffRoad++;
			}

			AverageHeight += HitData.Time * (m_SuspensionLength + m_WheelRadius);

			Wheels[WheelIndex]->SetWorldLocation(Arrows[WheelIndex]->GetComponentLocation() + Arrows[WheelIndex]->GetForwardVector() * (m_SuspensionLength + m_WheelRadius) * HitData.Time - (Arrows[WheelIndex]->GetForwardVector() * m_WheelRadius));
			
		}
		else {
			Wheels[WheelIndex]->SetWorldLocation(Arrows[WheelIndex]->GetComponentLocation() + Arrows[WheelIndex]->GetForwardVector() * (m_SuspensionLength));
		}
	
	}
	AverageHeight = AverageHeight / 4 - 2;
	SetBodyHeight(AverageHeight);
}



void ABaseKart::SetBodyHeight(float AverageWheelHeight)
{
	CollisionMesh->SetWorldLocation(CollisionMesh->GetComponentLocation() + CollisionMesh->GetUpVector() * AverageWheelHeight);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "debug msg");
}



void ABaseKart::CalculatebodyRotation()
{

}



void ABaseKart::CheckIfLanded()
{
	if (m_GroundedWheelsLastFrame == 0 && m_GroundedWheels > 0)
	{
		Landed();
	}
}

void ABaseKart::Landed()
{

}

void ABaseKart::DealWithGravity()
{
	if(m_GroundedWheels > 3)
	{
		CollisionMesh->AddForce(m_GravityDirection * m_GravityStrength);
	}
	else
	{
		FVector LinearVelocity = CollisionMesh->GetPhysicsLinearVelocity();
		// If 3 or more wheels are on the ground then eliminate gravity
		CollisionMesh->SetPhysicsLinearVelocity(LinearVelocity - FVector::DotProduct(LinearVelocity,CollisionMesh->GetUpVector()) * CollisionMesh->GetUpVector() * -1 );
	}
}


#pragma region NetworkingStuff

void ABaseKart::ServerRPCSendTurnAxis(float TurnAxis)
{
	MulticastRPCTurnAxis(TurnAxis);

}
bool ABaseKart::ServerRPCSendTurnAxis_Validate(float TurnAxis)
{
	if (FMath::Abs(TurnAxis) > 1.01f)
	{
		return false;                       // This will disconnect the caller
	}
	return true;                              // This will allow the RPC to be called
}
void ABaseKart::MulticastRPCTurnAxis(float TurnAxis)
{
	if (!IsLocallyControlled())
	{
		PerformTurning(TurnAxis);
	}
}



void ABaseKart::ServerRPCSendGasBreak(float GasAxis)
{
	MulticastRPCGasBreak(GasAxis);
}
bool ABaseKart::ServerRPCSendGasBreak_Validate(float GasAxis)
{
	if (FMath::Abs(GasAxis) > 1.01f)
	{
		return false;                       // This will disconnect the caller
	}
	return true;                              // This will allow the RPC to be called
}
void ABaseKart::MulticastRPCGasBreak(float GasAxis)
{
	if (!IsLocallyControlled())
	{
		PerformGasBreak(GasAxis);
	}
}

#pragma endregion


#pragma region InputFunctions

void ABaseKart::ApplyGasBreak(float AxisValue)
{
	ServerRPCSendGasBreak(FMath::Clamp(AxisValue, -1.0f, 1.0f));
	PerformGasBreak(FMath::Clamp(AxisValue, -1.0f, 1.0f));
}

void ABaseKart::Turn(float AxisValue)
{
	ServerRPCSendTurnAxis(FMath::Clamp(AxisValue, -1.0f, 1.0f));
	PerformTurning(FMath::Clamp(AxisValue, -1.0f, 1.0f));
}

void ABaseKart::LookBack()
{
}

void ABaseKart::DriftHop()
{

}

void ABaseKart::UseItem()
{
}

#pragma endregion

void ABaseKart::PerformTurning(float AxisValue)
{
	if (IsGrouned())
	{

		if (m_Drifting)
		{
			// The turn axis is modified based on whether the kart is turning
			// with or against a drift
			float ModifiedDriftAxis = 0;

			if (AxisValue / FMath::Abs(AxisValue) == m_DriftDirection / FMath::Abs(m_DriftDirection))
			{
				ModifiedDriftAxis = AxisValue * m_OuterDriftControlModifier;
			}
			else {
				ModifiedDriftAxis = AxisValue * m_InnerDriftControlModifier;
			}

			CollisionMesh->AddLocalRotation(FRotator(0.0f,0.0f, (m_DriftDirection * -m_AutomaticDriftRotation + ModifiedDriftAxis * m_OverallDriftControllModifier) * GetWorld()->GetDeltaSeconds()));
		}
		else { // if not drifting
			float ForwardReverseModifier = 1;
			if (FVector::DotProduct(CollisionMesh->GetPhysicsLinearVelocity(), CollisionMesh->GetForwardVector()) < 0)
			{
				ForwardReverseModifier = -1;
			}

			float TurnAmount = 0;
			float TurnLimiter = FMath::GetMappedRangeValueClamped(FVector2D(m_MaxSpeedForMaxTurnRadius, m_MaxSpeed), FVector2D(m_MinTurnRadius, m_MaxTurnRadius), FVector::DotProduct(CollisionMesh->GetPhysicsLinearVelocity(), CollisionMesh->GetForwardVector()));
			TurnAmount = FMath::Atan2(FVector::Dist(CollisionMesh->GetComponentLocation(), m_LocationLastFrame), TurnLimiter);

			CollisionMesh->AddLocalRotation(FRotator(0.0f,0.0f, TurnAmount));
		}
	}
	m_LocationLastFrame = CollisionMesh->GetComponentLocation();
	m_RotationToBeMaintained = CollisionMesh->GetComponentRotation();
}

void ABaseKart::PerformGasBreak(float AxisValue)
{
	if (IsGrouned())
	{

		float ForceToApply = 0;

		if (FVector::DotProduct(CollisionMesh->GetPhysicsLinearVelocity(), CollisionMesh->GetForwardVector()) > 0)
		{
			if (AxisValue > 0)
			{
				ForceToApply = m_AccelerationForce * AxisValue;
			}
			else {
				ForceToApply = -m_BreakForce * AxisValue;
			}
		}
		else 
		{
			if (AxisValue > 0)
			{
				ForceToApply = m_AccelerationForce * AxisValue;
			}
			else {
				ForceToApply = -m_ReverseForce * AxisValue;
			}
		}

		if(m_Drifting)
		{
			ApplyForce(FRotator(0,0, m_AutomaticDriftRotation).RotateVector(CollisionMesh->GetForwardVector() * ForceToApply));
		}
		else
		{
			ApplyForwardForce(ForceToApply);
		}
	}
}

bool ABaseKart::IsGrouned()
{
	if (m_GroundedWheels == 0)
	{
		return false;
	}
	return true;
}




