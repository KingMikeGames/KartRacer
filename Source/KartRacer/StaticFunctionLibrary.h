// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "StaticFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class KARTRACER_API UStaticFunctionLibrary : public UObject
{
	GENERATED_BODY()

public:
		//FORCEINLNE function
		static FORCEINLINE bool IsValid(AActor* TheActor)
	{
		if (!TheActor) return false;
		if (!TheActor->IsValidLowLevel()) return false;
		return true;
	}
	
	static FORCEINLINE bool Trace(
	UWorld* World,
	AActor* ActorToIgnore,	
	const FVector& Start, 
	const FVector& End, 
	FHitResult& HitOut,
	ECollisionChannel CollisionChannel = ECC_Pawn,
        bool ReturnPhysMat = false
) {
	if(!World) 
	{
		return false;
	}
	const FName TraceTag("MyTraceTag");

	World->DebugDrawTraceTag = TraceTag;

	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
	TraceParams.TraceTag = TraceTag;
	TraceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);
 
	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	//Trace!
	World->LineTraceSingleByChannel(
		HitOut,		//result
		Start,	//start
		End , //end
		CollisionChannel, //collision channel
		TraceParams
	);
 
	//Hit any Actor?
	return (HitOut.GetActor() != NULL) ;
	}
};
