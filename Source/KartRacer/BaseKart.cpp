// Fill out your copyright notice in the Description page of Project Settings.

#include "KartRacer.h"
#include "BaseKart.h"

#include "StaticFunctionLibrary.h"

// Sets default values
ABaseKart::ABaseKart() :
	m_WheelRadius(10),
	m_SuspensionLength(30)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Hit");

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
	SetBodyHeight(AverageHeight = AverageHeight / 4 - 2);
}

void ABaseKart::SetBodyHeight(float AverageWheelHeight)
{
	CollisionMesh->SetWorldLocation(CollisionMesh->GetComponentLocation() + CollisionMesh->GetUpVector() * AverageWheelHeight);
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

void ABaseKart::ApplyGasBreak(float AxisAngle)
{
}

void ABaseKart::Turn(float AxisAngle)
{
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



