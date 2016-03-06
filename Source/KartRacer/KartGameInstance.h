// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "KartGameInstance.generated.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelStruct", meta = (ClampMin = "0", ClampMax = "5", UIMin = "0", UIMax = "5"))
		int32 Rarity;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyStruct", meta = (ClampMin = "0", ClampMax = "5", UIMin = "0", UIMax = "5"))
		int32 Rarity;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PoofStruct", meta = (ClampMin = "0", ClampMax = "5", UIMin = "0", UIMax = "5"))
		int32 Rarity;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrailStruct", meta = (ClampMin = "0", ClampMax = "5", UIMin = "0", UIMax = "5"))
		int32 Rarity;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrickStruct", meta = (ClampMin = "0", ClampMax = "5", UIMin = "0", UIMax = "5"))
		int32 Rarity;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SparkStruct", meta = (ClampMin = "0", ClampMax = "5", UIMin = "0", UIMax = "5"))
		int32 Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SparkStruct")
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SparkStruct")
		UParticleSystem* BSparkParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SparkStruct")
		UParticleSystem* RSparkParticle;
};

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



USTRUCT(BlueprintType)
struct FPlayerInfo
{

	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		FName PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		int32 PlayerLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		int32 ExperiencePoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		int32 TrueSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		int32 WinStreak;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		float ExpMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		UTexture2D* PlayerImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerInfo)
		FInventoryStruct Inventory;
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

UCLASS()
class KARTRACER_API UKartGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UKartGameInstance();
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	FPlayerInfo PlayerInfo;

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
	
	UFUNCTION(BlueprintCallable, Category = "Database")
		TArray<int32> GetInventory(ETabEnum Tab);

	// player info

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		int32 AddExperience(int32 points);

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
		int32 LevelUp();
};
