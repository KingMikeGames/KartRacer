// Fill out your copyright notice in the Description page of Project Settings.

#include "KartRacer.h"
#include "Kart.h"


// Sets default values
AKart::AKart() :
	NetworkInitialized(false),
	IsRealKart(false),
	NetworkLerpTimer(0),
	TimerNetworkLerp(1.0f/120.0f),
	TimerNetworkSend(1.0f/30.0f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKart::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AKart::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AKart::RPC_SendData(FNetworkData Data)
{
	RPC_SetData(Data);
}

void AKart::RPC_SetData(FNetworkData Data)
{
	if (!IsRealKart)
	{
		NetworkDataArray.Add(Data);
	}
}

void AKart::DealWithNetworking()
{
	if (!IsRealKart && NetworkInitialized && NetworkDataArray.Num() > 2)
	{

	}
}

