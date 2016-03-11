// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Kart.generated.h"

USTRUCT()
struct FNetworkData
{
	GENERATED_BODY()

	FTransform transform;
	float DriftTimer;
	bool Drift;
	FVector LastCheckpointPosition;
	float DistanceTravelled;
};

UCLASS()
class KARTRACER_API AKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AKart();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:
	FVector PositionLastFrame;

	/** Can Startrunning network functions */
	bool NetworkInitialized;

	/** The timer to be used for alpha */
	float NetworkLerpTimer;

	/** The loop timer for the network functions*/
	float TimerNetworkLerp;
	float TimerNetworkSend;

	/** If true this will be the kart that sends data to the server */
	bool IsRealKart;

	TArray<FNetworkData> NetworkDataArray;

	/** Send data to the server */
	UFUNCTION(reliable, server, WithValidation)
	void RPC_SendData(FNetworkData Data);
	/** Take the data sent to the server and send it to all the clients */
	UFUNCTION(reliable, NetMulticast, WithValidation)
	void RPC_SetData(FNetworkData Data);
	/** Interpolate through the data recieved */
	void DealWithNetworking();


};
