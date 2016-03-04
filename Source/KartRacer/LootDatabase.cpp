// Fill out your copyright notice in the Description page of Project Settings.

#include "KartRacer.h"
#include "LootDatabase.h"

ULootDatabase::ULootDatabase()
{

}

FBodyStruct ULootDatabase::GetBodyByID(int32 ID)
{
	return BodyDB[ID];
}

FWheelStruct ULootDatabase::GetWheelByID(int32 ID)
{
	return WheelDB[ID];
}

FPoofStruct ULootDatabase::GetPoofByID(int32 ID)
{
	return PoofDB[ID];
}

FTrailStruct ULootDatabase::GetTrailByID(int32 ID)
{
	return TrailDB[ID];
}

FTrickStruct ULootDatabase::GetTrickByID(int32 ID)
{
	return TrickDB[ID];
}

FSparkStruct ULootDatabase::GetSparkByID(int32 ID)
{
	return SparkDB[ID];
}
