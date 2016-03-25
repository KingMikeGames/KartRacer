// Fill out your copyright notice in the Description page of Project Settings.

#include "KartRacer.h"
#include "BaseKart.h"
#include "StaticFunctionLibrary.h"
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetSystemLibrary.h>
#include "KartGameInstance.h"

// Sets default values
ABaseKart::ABaseKart() :
	m_WheelRadius(13),
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
	m_MaxSpeedForMaxTurnRadius(750.0f),
	m_MaxSpeed(4000),
	m_MinTurnRadius(1000),
	m_MaxTurnRadius(4000),
	m_AccelerationForce(2500),
	m_ReverseForce(1250),
	m_BreakForce(2500),
	m_InTrickVolume(false),
	m_CanTrick(true),
	m_TrickForceAir(500.0f),
	m_DriftButtonHeld(false),
	m_HopPower(1000.0f),
	m_DeadZone(0.1f),
	m_DriftTimer(0.0f),
	m_DriftReady(true),
	m_MiniDriftBoostChargeTime(1.0f),
	m_MegaDriftBoostChargeTime(3.0f),
	m_MiniDriftBoostForce(500.0f),
	m_MegaDriftBoostForce(1000.0f),
	m_MinDriftSpeed(600.0f),
	m_OnDriftVelocityRotationInDegrees(10.0f),
	m_HasTrickBoost(false),
	m_TrickForceLanded(500),
	m_ForwardVectorFromWheels(0.0f, 0.0f, 0.0f),
	m_RightVectorFromWheels(0.0f, 0.0f, 0.0f),
	m_GroundRInterpSpeed(0.0f),
	m_AirRInterpSpeed(75.0f),
	m_SlideResistance(1.5),
	m_OffRoadSlowDownPerWheel(0.25f),
	m_ControlsEnabled(false),
	UpdateSparks(true),
	UpdateTrails(true),
	UpdatePoof(true),
	UpdateBody(true),
	UpdateWheels(true),
	UpdateTrick(true),
	TurnValue(0.0f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetTickGroup(TG_PostPhysics);

	

#pragma region ComponentInit
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollisionRoot"));
	RootComponent = CollisionMesh;
	CollisionMesh->SetSimulatePhysics(true);
	CollisionMesh->SetEnableGravity(false);
	CollisionMesh->SetLinearDamping(1.0f);
	CollisionMesh->SetAngularDamping(2.0f);
	CollisionMesh->bHiddenInGame = true;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	BodyMesh->AttachTo(RootComponent);

#pragma region Arrow Initialization
	FrontRightArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FrontRightArrow"));
	FrontRightArrow->AttachTo(RootComponent);
	Arrows.Add(FrontRightArrow);

	FrontLeftArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FrontLeftArrow"));
	FrontLeftArrow->AttachTo(RootComponent);
	Arrows.Add(FrontLeftArrow);

	BackRightArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("BackRightArrow"));
	BackRightArrow->AttachTo(RootComponent);
	Arrows.Add(BackRightArrow);

	BackLeftArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("BackLeftArrow"));
	BackLeftArrow->AttachTo(RootComponent);
	Arrows.Add(BackLeftArrow);
#pragma endregion

#pragma region Wheel Initialization
	FrontRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontRightWheel"));
	FrontRightWheel->AttachTo(RootComponent);
	Wheels.Add(FrontRightWheel);

	FrontLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontLeftWheel"));
	FrontLeftWheel->AttachTo(RootComponent);
	Wheels.Add(FrontLeftWheel);

	BackRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackRightWheel"));
	BackRightWheel->AttachTo(RootComponent);
	Wheels.Add(BackRightWheel);

	BackLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackLeftWheel"));
	BackLeftWheel->AttachTo(RootComponent);
	Wheels.Add(BackLeftWheel);
#pragma endregion

	BSparkRight = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BSparkRight"));
	BSparkRight->AttachTo(RootComponent);
	BSparkRight->bAutoActivate = false;

	BSparkLeft = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BSparkLeft"));
	BSparkLeft->AttachTo(RootComponent);
	BSparkLeft->bAutoActivate = false;

	RSparkRight = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RSparkRight"));
	RSparkRight->AttachTo(RootComponent);
	RSparkRight->bAutoActivate = false;

	RSparkLeft = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RSparkLeft"));
	RSparkLeft->AttachTo(RootComponent);
	RSparkLeft->bAutoActivate = false;

	TrailEmitterRight = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEmitterRight"));
	TrailEmitterRight->AttachTo(RootComponent);
	TrailEmitterRight->bAutoActivate = false;

	TrailEmitterLeft = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEmitterLeft"));
	TrailEmitterLeft->AttachTo(RootComponent);
	TrailEmitterLeft->bAutoActivate = false;

	TrickEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrickEmitter"));
	TrickEmitter->AttachTo(RootComponent);
	TrickEmitter->bAutoActivate = false;

	PoofEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PoofEmitter"));
	PoofEmitter->AttachTo(RootComponent);
	PoofEmitter->bAutoActivate = false;
	

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraLagSpeed = 15.0f;
	CameraBoom->CameraRotationLagSpeed = 10.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(CameraBoom);

	
#pragma endregion

}

// Called when the game starts or when spawned
void ABaseKart::BeginPlay()
{
	Super::BeginPlay();
	m_LocationLastFrame = CollisionMesh->GetComponentLocation();
	UpdateKartComponents();

	m_RotationToBeMaintained = CollisionMesh->GetComponentRotation();

	UpdateWheelPositions();

	

	BSparkRight->SetWorldLocation(BodyMesh->GetSocketLocation("BackRight"));
	BSparkLeft->SetWorldLocation(BodyMesh->GetSocketLocation("BackLeft"));
	RSparkRight->SetWorldLocation(BodyMesh->GetSocketLocation("BackRight"));
	RSparkLeft->SetWorldLocation(BodyMesh->GetSocketLocation("BackLeft"));
	TrailEmitterRight->SetWorldLocation(BodyMesh->GetSocketLocation("BackRight"));
	TrailEmitterLeft->SetWorldLocation(BodyMesh->GetSocketLocation("BackLeft"));
	FrontWheelStart = FrontLeftWheel->GetComponentRotation().Yaw;

	UpdateSuspension();
}

// Called every frame
void ABaseKart::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (m_ControlsEnabled  && !doOnce)
	{
		if (IsLocallyControlled())
		{
			doOnce = true;
			UKartGameInstance* KartGameInstance = Cast<UKartGameInstance>(GetGameInstance());
			FEquipment Equips = KartGameInstance->PlayerInfo.CurrentlyEquipped;
			SendKartComponentsToServer(Equips.Body, Equips.Wheel, Equips.Trail, Equips.Spark, Equips.Trick, Equips.Poof);
			GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, "Changing Parts 1");
		}
	}

	if (!IsLocallyControlled())
	{
		UpdateSuspension();
	}

	if (IsLocallyControlled())
	{
		if (CollisionMesh->GetPhysicsLinearVelocity().Size() < m_MinDriftSpeed)
		{
			EndDrift();
		}
	m_GravityDirection = GetGravityDirection();
	UpdateSuspension();
	ResetRotation();
	CheckIfLanded();
	//CalculatebodyRotation();
	DealWithGravity();
	ResetRotation();
	SetForwardVectorFromWheels();
	SetRightVectorFromWheels();
	RotationInterpolation(DeltaTime);
	DriftPhysics(DeltaTime);
	SetLinearDamping();
	}
}



// Called to bind functionality to input
void ABaseKart::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("Accelerate", this, &ABaseKart::ApplyGasBreak);
	InputComponent->BindAxis("Turn", this, &ABaseKart::Turn);

	InputComponent->BindAction("LookBack", IE_Pressed, this, &ABaseKart::LookBackPressed);
	InputComponent->BindAction("LookBack", IE_Released, this, &ABaseKart::LookBackReleased);
	InputComponent->BindAction("DriftHop", IE_Pressed, this, &ABaseKart::HopPressed);
	InputComponent->BindAction("DriftHop", IE_Released, this, &ABaseKart::HopReleased);
	InputComponent->BindAction("UseItem", IE_Pressed, this, &ABaseKart::UseItem);
}



void ABaseKart::ApplyForwardForce(float Force)
{
	CollisionMesh->AddForce(CollisionMesh->GetForwardVector() * Force,NAME_None,true);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::SanitizeFloat(Force));
}

void ABaseKart::ApplyForce(FVector Force)
{
	CollisionMesh->AddForce(Force, NAME_None, true);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::SanitizeFloat(Force.Size()));
}

void ABaseKart::ApplyForwardImpulse(float Force)
{
	CollisionMesh->AddImpulse(CollisionMesh->GetForwardVector() * Force, NAME_None, true);
	
}

void ABaseKart::ApplyImpulse(FVector Force)
{
	CollisionMesh->AddImpulse(Force, NAME_None, true);
}

void ABaseKart::UpdateKartComponents()
{
	UKartGameInstance* KartGameInstance = Cast<UKartGameInstance>(GetGameInstance());
	if (KartGameInstance)
	{
		FEquipment Equips = KartGameInstance->PlayerInfo.CurrentlyEquipped;

		if (UpdateBody)
		{
			BodyMesh->SetStaticMesh(KartGameInstance->GetBodyByID(Equips.Body).BodyMesh);
			UpdateBody = false;
			UpdateWheelPositions();
		}
		if (UpdateWheels)
		{
			for (auto e : Wheels)
			{
				e->SetStaticMesh(KartGameInstance->GetWheelByID(Equips.Wheel).WheelMesh);
			}
			UpdateWheels = false;
		}
		if (UpdateTrails)
		{
			TrailEmitterLeft->SetTemplate(KartGameInstance->GetTrailByID(Equips.Trail).TrailParticle);
			TrailEmitterRight->SetTemplate(KartGameInstance->GetTrailByID(Equips.Trail).TrailParticle);
			UpdateTrails = false;
		}
		if (UpdateSparks)
		{
			BSparkLeft->SetTemplate(KartGameInstance->GetSparkByID(Equips.Spark).BSparkParticle);
			BSparkRight->SetTemplate(KartGameInstance->GetSparkByID(Equips.Spark).BSparkParticle);
			RSparkLeft->SetTemplate(KartGameInstance->GetSparkByID(Equips.Spark).RSparkParticle);
			RSparkRight->SetTemplate(KartGameInstance->GetSparkByID(Equips.Spark).RSparkParticle);
			UpdateSparks = false;
		}
		if (UpdateTrick)
		{
			TrickEmitter->SetTemplate(KartGameInstance->GetTrickByID(Equips.Trick).TrickParticle);
			UpdateTrick = false;
		}
		if (UpdatePoof)
		{
			PoofEmitter->SetTemplate(KartGameInstance->GetPoofByID(Equips.Poof).PoofParticle);
			UpdatePoof = false;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Red, "Failed to cast game instance to kart game instance");
	}

}

bool ABaseKart::SendKartComponentsToServer_Validate(int Body, int Wheel, int Trail, int Spark, int Trick, int Poof)
{
	if (Body >= 0 && Wheel >= 0 && Trail >= 0 && Spark >= 0 && Trick >= 0 && Poof >= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, "Changing Parts 2");
		return true;
	}
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, "Changing Parts FUCKED UP");
	return false;
}


void ABaseKart::SendKartComponentsToServer_Implementation(int Body, int Wheel, int Trail, int Spark, int Trick, int Poof)
{
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, "Changing Parts 3");
	SendKartComponentsToAllClients(Body, Wheel, Trail, Spark, Trick, Poof);
}

void ABaseKart::SendKartComponentsToAllClients_Implementation(int Body, int Wheel, int Trail, int Spark, int Trick, int Poof)
{
	if (!IsLocallyControlled())
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, "Changing Parts 4");
		SetKartComponents(Body,  Wheel,  Trail,  Spark,  Trick,  Poof);
	}
}

void ABaseKart::SetKartComponents(int Body, int Wheel, int Trail, int Spark, int Trick, int Poof)
{
	UKartGameInstance* KartGameInstance = Cast<UKartGameInstance>(GetGameInstance());
	if (KartGameInstance)
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, "Changing Parts 5");
	
			BodyMesh->SetStaticMesh(KartGameInstance->GetBodyByID(Body).BodyMesh);
			UpdateWheelPositions();

			for (auto e : Wheels)
			{
				e->SetStaticMesh(KartGameInstance->GetWheelByID(Wheel).WheelMesh);
			}
		
			TrailEmitterLeft->SetTemplate(KartGameInstance->GetTrailByID(Trail).TrailParticle);
			TrailEmitterRight->SetTemplate(KartGameInstance->GetTrailByID(Trail).TrailParticle);
			
			BSparkLeft->SetTemplate(KartGameInstance->GetSparkByID(Spark).BSparkParticle);
			BSparkRight->SetTemplate(KartGameInstance->GetSparkByID(Spark).BSparkParticle);
			RSparkLeft->SetTemplate(KartGameInstance->GetSparkByID(Spark).RSparkParticle);
			RSparkRight->SetTemplate(KartGameInstance->GetSparkByID(Spark).RSparkParticle);
			
			TrickEmitter->SetTemplate(KartGameInstance->GetTrickByID(Trick).TrickParticle);
			
			PoofEmitter->SetTemplate(KartGameInstance->GetPoofByID(Poof).PoofParticle);
			UpdatePoof = false;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Red, "Failed to cast game instance to kart game instance");
	}

}

void ABaseKart::SparkLogic()
{
	if (m_Drifting)
	{
		if (m_DriftTimer < m_MiniDriftBoostChargeTime)
		{
			BSparkLeft->SetActive(false);
			BSparkRight->SetActive(false);
			RSparkLeft->SetActive(false);
			RSparkRight->SetActive(false);
			TrailEmitterLeft->SetActive(true);
			TrailEmitterRight->SetActive(true);
		}
		else if (m_DriftTimer >= m_MiniDriftBoostChargeTime && m_DriftTimer < m_MegaDriftBoostChargeTime)
		{
			BSparkLeft->SetActive(true);
			BSparkRight->SetActive(true);
			RSparkLeft->SetActive(false);
			RSparkRight->SetActive(false);
			TrailEmitterLeft->SetActive(true);
			TrailEmitterRight->SetActive(true);
		}
		else if (m_DriftTimer >= m_MegaDriftBoostChargeTime)
		{
			BSparkLeft->SetActive(false);
			BSparkRight->SetActive(false);
			RSparkLeft->SetActive(true);
			RSparkRight->SetActive(true);
			TrailEmitterLeft->SetActive(true);
			TrailEmitterRight->SetActive(true);
		}
	}
	else
	{
		BSparkLeft->SetActive(false);
		BSparkRight->SetActive(false);
		RSparkLeft->SetActive(false);
		RSparkRight->SetActive(false);
		TrailEmitterLeft->SetActive(false);
		TrailEmitterRight->SetActive(false);

	}
}

void ABaseKart::SpawnEmitter_Implementation(UParticleSystemComponent* emitter)
{
	//Implemented in BP
}


void ABaseKart::ResetRotation()
{
	if (IsLocallyControlled())
	{
		CollisionMesh->SetWorldRotation(m_RotationToBeMaintained);
	}
}

FVector ABaseKart::GetGravityDirection_Implementation()
{
	return FVector(0, 0, -1);
}



void ABaseKart::UpdateSuspension()
{
	UWorld* World = GetWorld();
	float AverageHeight = 0;
	m_GroundedWheelsLastFrame = m_GroundedWheels;
	m_GroundedWheels = 0;
	m_WheelsOffRoad = 0;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);


	for (size_t WheelIndex = 0; WheelIndex < Arrows.Num(); WheelIndex++)
	{
		
		FHitResult HitData(ForceInit);
		bool hit = UKismetSystemLibrary::SphereTraceSingle_NEW(World, Arrows[WheelIndex]->GetComponentLocation(), Arrows[WheelIndex]->GetComponentLocation() + Arrows[WheelIndex]->GetForwardVector() * (m_SuspensionLength), m_WheelRadius,ETraceTypeQuery::TraceTypeQuery1, true, ActorsToIgnore ,EDrawDebugTrace::None, HitData, ECC_GameTraceChannel1);
		
		if (hit)
		{
			m_GroundedWheels++;
			//

			if (HitData.PhysMaterial->Friction > 1)
			{
				m_WheelsOffRoad++;
			}

			AverageHeight += (m_SuspensionLength) - ((m_SuspensionLength) * HitData.Time);

			Wheels[WheelIndex]->SetWorldLocation(Arrows[WheelIndex]->GetComponentLocation() + Arrows[WheelIndex]->GetForwardVector() * (m_SuspensionLength) * HitData.Time);
			
		}
		else {
			Wheels[WheelIndex]->SetWorldLocation(Arrows[WheelIndex]->GetComponentLocation() + Arrows[WheelIndex]->GetForwardVector() * (m_SuspensionLength));
		}
	
	}
	AverageHeight = AverageHeight / 4 - 2;
	CollisionMesh->SetWorldLocation(CollisionMesh->GetComponentLocation() + CollisionMesh->GetUpVector() * AverageHeight);
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
	if (!m_Drifting && m_DriftButtonHeld && m_DriftReady && m_DriftDirection != 0 && FVector::DotProduct(CollisionMesh->GetPhysicsLinearVelocity(), CollisionMesh->GetForwardVector()) > m_MinDriftSpeed)
	{
		LandedInDrift();
	}
	if (m_HasTrickBoost)
	{
		m_HasTrickBoost = false;
		ApplyForwardImpulse(m_TrickForceLanded);
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Poof");
	SpawnEmitter(PoofEmitter);
}

void ABaseKart::DealWithGravity()
{
	if(m_GroundedWheels > 3)
	{
		FVector LinearVelocity = CollisionMesh->GetPhysicsLinearVelocity();
		// If 3 or more wheels are on the ground then eliminate gravity
		CollisionMesh->SetPhysicsLinearVelocity(LinearVelocity - FVector::DotProduct(LinearVelocity, -CollisionMesh->GetUpVector()) * -CollisionMesh->GetUpVector());
	}
	else
	{
		CollisionMesh->AddForce(m_GravityDirection * m_GravityStrength, NAME_None, true);
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Not Grounded");
	}
}

void ABaseKart::Turn(float AxisValue)
{
	AxisValue = FMath::Clamp(AxisValue, -1.0f, 1.0f);
	TurnValue = AxisValue;

	if (m_ControlsEnabled)
	{
		if (IsGrounded())
		{
			if (m_Drifting)
			{
				// The turn axis is modified based on whether the kart is turning
				// with or against a drift
				float ModifiedDriftAxis = 0;
				if (AxisValue / FMath::Abs(AxisValue) == m_DriftDirection / FMath::Abs(m_DriftDirection))
				{
					ModifiedDriftAxis = AxisValue * m_InnerDriftControlModifier;
				}
				else {
					ModifiedDriftAxis = AxisValue * m_OuterDriftControlModifier;
				}

				CollisionMesh->AddLocalRotation(FRotator(0.0f, (m_DriftDirection * m_AutomaticDriftRotation + ModifiedDriftAxis * m_OverallDriftControllModifier) * GetWorld()->GetDeltaSeconds(), 0.0f));
			}
			else { // if not drifting


				float ForwardReverseModifier = 1;
				if (FVector::DotProduct(CollisionMesh->GetPhysicsLinearVelocity(), CollisionMesh->GetForwardVector()) < 0)
				{
					ForwardReverseModifier = -1;
				}

				float TurnAmount = 0;
				float TurnLimiter = FMath::GetMappedRangeValueClamped(FVector2D(m_MaxSpeedForMaxTurnRadius, m_MaxSpeed), FVector2D(m_MinTurnRadius, m_MaxTurnRadius), FVector::DotProduct(CollisionMesh->GetPhysicsLinearVelocity(), CollisionMesh->GetForwardVector()));
				TurnAmount = FMath::RadiansToDegrees(FMath::Atan2(FVector::Dist(CollisionMesh->GetComponentLocation(), m_LocationLastFrame), TurnLimiter));

				CollisionMesh->AddLocalRotation(FRotator(0.0f, TurnAmount * ForwardReverseModifier * AxisValue, 0.0f));
			}
		}
		m_LocationLastFrame = CollisionMesh->GetComponentLocation();
		m_RotationToBeMaintained = CollisionMesh->GetComponentRotation();
	}
}

void ABaseKart::ApplyGasBreak(float AxisValue)
{
	AxisValue = FMath::Clamp(AxisValue, -1.0f, 1.0f);

	if (m_ControlsEnabled)
	{
		if (IsGrounded())
		{
			float ForceToApply = 0;

			if (AxisValue > 0)
			{
				ForceToApply = m_AccelerationForce * AxisValue;
			}
			else {
				if (FVector::DotProduct(CollisionMesh->GetPhysicsLinearVelocity(), CollisionMesh->GetForwardVector()) > 20)
				{
					ForceToApply = m_BreakForce * AxisValue;
				}
				else {
					ForceToApply = m_ReverseForce * AxisValue;
				}
			}

			if (m_Drifting)
			{
				ApplyForce((FRotator(0, -m_AutomaticDriftRotation * m_DriftDirection, 0).RotateVector(CollisionMesh->GetForwardVector()) * ForceToApply));
			}
			else
			{
				ApplyForwardForce(ForceToApply);
			}
		}
	}
}


void ABaseKart::EnableCameraLag()
{
	CameraBoom->bEnableCameraLag = true;
}

void ABaseKart::SetForwardVectorFromWheels()
{
	m_ForwardVectorFromWheels = ((Wheels[0]->GetComponentLocation() - Wheels[2]->GetComponentLocation()).GetSafeNormal() + (Wheels[1]->GetComponentLocation() - Wheels[3]->GetComponentLocation()).GetSafeNormal()).GetSafeNormal();
}

void ABaseKart::SetRightVectorFromWheels()
{
	m_RightVectorFromWheels = ((Wheels[0]->GetComponentLocation() - Wheels[1]->GetComponentLocation()).GetSafeNormal() + (Wheels[2]->GetComponentLocation() - Wheels[3]->GetComponentLocation()).GetSafeNormal()).GetSafeNormal();
}

void ABaseKart::RotationInterpolation(float DeltaTime)
{
	ResetRotation();
	FVector OldForwardVector = CollisionMesh->GetForwardVector();
	FVector UpVector = IsGrounded() ? FVector::CrossProduct(m_ForwardVectorFromWheels, m_RightVectorFromWheels) : -m_GravityDirection;
	FRotator TargetRotation = FRotator::MakeFromEuler(FVector(UKismetMathLibrary::MakeRotFromZX(UpVector, m_ForwardVectorFromWheels).Roll,UKismetMathLibrary::MakeRotFromYZ(m_RightVectorFromWheels,UpVector).Pitch,UKismetMathLibrary::MakeRotFromXY(m_ForwardVectorFromWheels,m_RightVectorFromWheels).Yaw));
	FRotator NewRotation(FMath::RInterpConstantTo(m_RotationToBeMaintained,TargetRotation,DeltaTime,IsGrounded() ? m_GroundRInterpSpeed : m_AirRInterpSpeed));
	CollisionMesh->SetWorldRotation(FRotator::MakeFromEuler(FVector(NewRotation.Roll, NewRotation.Pitch, TargetRotation.Yaw)));
	FVector NewForwardVector = CollisionMesh->GetForwardVector();
	if (m_GroundedWheels == 4)
	{
		float SpeedToGetRotated = FVector::DotProduct(CollisionMesh->GetPhysicsLinearVelocity(), OldForwardVector);
		CollisionMesh->SetPhysicsLinearVelocity( (CollisionMesh->GetPhysicsLinearVelocity() - OldForwardVector * SpeedToGetRotated) + (NewForwardVector * SpeedToGetRotated) );
	}
	m_RotationToBeMaintained = CollisionMesh->GetComponentRotation();
}

void ABaseKart::DriftPhysics(float DeltaTime)
{
	if (IsGrounded())
	{
		if (m_Drifting)
		{
			m_DriftTimer += DeltaTime;
		}
		ApplyForce(-FVector::DotProduct(CollisionMesh->GetPhysicsLinearVelocity(),CollisionMesh->GetRightVector()) * CollisionMesh->GetRightVector() * m_SlideResistance);
	}
}

void ABaseKart::SetLinearDamping()
{
	if (IsGrounded())
	{
		CollisionMesh->SetLinearDamping(1 + m_OffRoadSlowDownPerWheel * m_WheelsOffRoad);
	}
	else
	{
		CollisionMesh->SetLinearDamping(0.1f);
	}
}

void ABaseKart::UpdateWheelPositions()
{
	FrontRightArrow->SetWorldLocation(BodyMesh->GetSocketLocation("FrontRight") + BodyMesh->GetUpVector() * FVector(1, 1, m_SuspensionLength));
	FrontLeftArrow->SetWorldLocation(BodyMesh->GetSocketLocation("FrontLeft") + BodyMesh->GetUpVector() * FVector(1, 1, m_SuspensionLength));
	BackRightArrow->SetWorldLocation(BodyMesh->GetSocketLocation("BackRight") + BodyMesh->GetUpVector() * FVector(1, 1, m_SuspensionLength));
	BackLeftArrow->SetWorldLocation(BodyMesh->GetSocketLocation("BackLeft") + BodyMesh->GetUpVector() * FVector(1, 1, m_SuspensionLength));
}

void ABaseKart::LookBackPressed()
{
	if (m_ControlsEnabled)
	{
		CameraBoom->bEnableCameraLag = false;
		CameraBoom->SetRelativeRotation(FRotator(-15.0f, 180.0f, 0.0f));
		GetWorldTimerManager().SetTimer(m_CameraLagTimerHandle, this, &ABaseKart::EnableCameraLag, 0.1f);
	}
}

void ABaseKart::LookBackReleased()
{
	if (m_ControlsEnabled)
	{
		CameraBoom->bEnableCameraLag = false;
		CameraBoom->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
		GetWorldTimerManager().SetTimer(m_CameraLagTimerHandle, this, &ABaseKart::EnableCameraLag, 0.1f);
	}
}

void ABaseKart::HopPressed()
{
	if (m_ControlsEnabled)
	{
		if (m_InTrickVolume)
		{
			if (m_CanTrick)
			{
				ApplyForwardImpulse(m_TrickForceAir);
				SpawnEmitter(TrickEmitter);
				m_HasTrickBoost = true;
			}
		}
		m_DriftButtonHeld = true;
		if (IsGrounded())
		{
			//ApplyImpulse(CollisionMesh->GetUpVector() * m_HopPower);
			float TurnValue = GetInputAxisValue("Turn");
			if (TurnValue < -m_DeadZone)
			{
				m_DriftDirection = -1;
				if (FVector::DotProduct(CollisionMesh->GetPhysicsLinearVelocity(), CollisionMesh->GetForwardVector()) > m_MinDriftSpeed)
				{
					LandedInDrift();
				}
			}
			else if (TurnValue > m_DeadZone) {
				m_DriftDirection = 1;
				if (FVector::DotProduct(CollisionMesh->GetPhysicsLinearVelocity(), CollisionMesh->GetForwardVector()) > m_MinDriftSpeed)
				{
					LandedInDrift();
				}
			}
			else
			{
				m_DriftDirection = 0;
			}

			//TODO: Figure out if we're using animations for drift hops
		}
	}
}

void ABaseKart::HopReleased()
{
	if (m_ControlsEnabled)
	{
		if (m_Drifting)
		{
			if (m_DriftTimer > 3.0f)
			{
				ApplyForwardImpulse(m_MegaDriftBoostForce);
			}
			else if (m_DriftTimer > 1.0f)
			{
				ApplyForwardImpulse(m_MiniDriftBoostForce);
			}
		}
		EndDrift();
	}
}

void ABaseKart::EndDrift()
{
	m_DriftTimer = 0.0f;
	m_Drifting = false;
	m_DriftReady = true;
	m_DriftButtonHeld = false;
}

void ABaseKart::LandedInDrift()
{
	m_Drifting = true;
	CollisionMesh->SetPhysicsLinearVelocity(FRotator(0.0f, -m_OnDriftVelocityRotationInDegrees * m_DriftDirection, 0.0f).RotateVector(CollisionMesh->GetPhysicsLinearVelocity()));
	m_DriftReady = true;
}



void ABaseKart::UseItem()
{
	if (m_ControlsEnabled)
	{

	}
}




bool ABaseKart::IsGrounded()
{
	if (m_GroundedWheels == 0)
	{
		return false;
	}
	return true;
}




