// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Inventory.generated.h"

/**
 * 
 */





UCLASS()
class KARTRACER_API UInventory : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryArrays")
	TArray<int32> BodyInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryArrays")
	TArray<int32> WheelInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryArrays")
	TArray<int32> PoofInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryArrays")
	TArray<int32> TrailInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryArrays")
	TArray<int32> TrickInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryArrays")
	TArray<int32> SparkInventory;
};
