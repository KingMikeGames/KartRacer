// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "PlayerData.generated.h"

/**
 * 
 */



USTRUCT(BlueprintType)
struct FInventoryStruct
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<int32> BodyInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<int32> WheelInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<int32> PoofInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<int32> TrailInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<int32> TrickInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<int32> SparkInventory;
};


UCLASS(Blueprintable)
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
		int32 ExperiencePoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		int32 TrueSkill;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		int32 WinStreak;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		float ExpMultiplier;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		UTexture2D* PlayerImage;
	
	UFUNCTION(BlueprintCallable, Category = PlayerInfo)
		int32 AddExperience(int32 points);

	UFUNCTION(BlueprintCallable, Category = PlayerInfo)
		int32 LevelUp();
};
