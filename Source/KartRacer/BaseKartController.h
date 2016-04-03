// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BaseKartController.generated.h"

/**
 * 
 */

UCLASS()
class KARTRACER_API ABaseKartController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart Status")
		bool HasItem;

	
};
