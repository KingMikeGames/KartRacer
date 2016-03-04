// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "PlayerData.generated.h"

/**
 * 
 */
UCLASS()
class KARTRACER_API UPlayerData : public UObject
{
	GENERATED_BODY()
	
public:
	UPlayerData();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		FName PlayerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		int32 PlayerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		int32 TrueSkill;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		UTexture2D* PlayerImage;
	
};
