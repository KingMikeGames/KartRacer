// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "LootDatabase.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FWheelStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelStruct")
		int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelStruct")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelStruct")
		uint8 Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelStruct")
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelStruct")
		UStaticMesh* WheelMesh;
};

USTRUCT(BlueprintType)
struct FBodyStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyStruct")
		int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyStruct")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyStruct")
		uint8 Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyStruct")
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyStruct")
		UStaticMesh* BodyMesh;
};

USTRUCT(BlueprintType)
struct FPoofStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PoofStruct")
		int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PoofStruct")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PoofStruct")
		uint8 Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PoofStruct")
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PoofStruct")
		UParticleSystem* PoofParticle;
};

USTRUCT(BlueprintType)
struct FTrailStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrailStruct")
		int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrailStruct")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrailStruct")
		uint8 Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrailStruct")
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrailStruct")
		UParticleSystem* TrailParticle;
};

USTRUCT(BlueprintType)
struct FTrickStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrickStruct")
		int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrickStruct")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrickStruct")
		uint8 Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrickStruct")
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrickStruct")
		UParticleSystem* TrickParticle;
};

USTRUCT(BlueprintType)
struct FSparkStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SparkStruct")
		int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SparkStruct")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SparkStruct")
		uint8 Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SparkStruct")
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SparkStruct")
		UParticleSystem* BSparkParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SparkStruct")
		UParticleSystem* RSparkParticle;
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ETabEnum : uint8
{
	VE_Body 	UMETA(DisplayName = "Body"),
	VE_Wheel 	UMETA(DisplayName = "Wheel"),
	VE_Spark	UMETA(DisplayName = "Spark"),
	VE_Trail	UMETA(DisplayName = "Trail"),
	VE_Poof		UMETA(DisplayName = "Poof"),
	VE_Trick	UMETA(DisplayName = "Trick")
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ESortType : uint8
{
	VE_AlphaNumeric 	UMETA(DisplayName = "AlphaNumeric"),
	VE_Rarity 			UMETA(DisplayName = "Rarity")
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EDirection : uint8
{
	VE_Ascending	UMETA(DisplayName = "Ascending"),
	VE_Descending 	UMETA(DisplayName = "Descending"),
};

UCLASS(Blueprintable)
class KARTRACER_API ULootDatabase : public UObject
{
	GENERATED_BODY()
public:

	ULootDatabase();

	//DataBase
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
		TArray<FBodyStruct> BodyDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
		TArray<FWheelStruct> WheelDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
		TArray<FPoofStruct> PoofDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
		TArray<FTrailStruct> TrailDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
		TArray<FTrickStruct> TrickDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Database")
		TArray<FSparkStruct> SparkDB;

	//Database accessors 
	UFUNCTION(BlueprintCallable, Category = "Database")
		FBodyStruct GetBodyByID(int32 ID);
	UFUNCTION(BlueprintCallable, Category = "Database")
		FWheelStruct GetWheelByID(int32 ID);
	UFUNCTION(BlueprintCallable, Category = "Database")
		FPoofStruct GetPoofByID(int32 ID);
	UFUNCTION(BlueprintCallable, Category = "Database")
		FTrailStruct GetTrailByID(int32 ID);
	UFUNCTION(BlueprintCallable, Category = "Database")
		FTrickStruct GetTrickByID(int32 ID);
	UFUNCTION(BlueprintCallable, Category = "Database")
		FSparkStruct GetSparkByID(int32 ID);

	// Loot Sorting
	UFUNCTION(BlueprintCallable, Category = "ArraySorting")
		TArray<int32> SortInventory(TArray<int32> Items, ETabEnum Type, ESortType SortType, EDirection Direction);
};
