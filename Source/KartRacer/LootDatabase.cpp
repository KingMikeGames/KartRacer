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

TArray<int32> ULootDatabase::SortInventory(TArray<int32> Items, ETabEnum Type, ESortType SortType, EDirection Direction)
{
	TArray<int32> Ret;

	switch (Type)
	{
	case ETabEnum::VE_Body:
	{
		// body sort start -----------------------------------------------------------
		TArray<FBodyStruct> Temp;
		for (size_t i = 0; i < Items.Max(); i++)
		{
			Temp.Add(GetBodyByID(Items[i]));
		}
		switch (SortType)
		{
		case ESortType::VE_AlphaNumeric:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FBodyStruct& One, const FBodyStruct& Two) {
					return One.Name < Two.Name;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FBodyStruct& One, const FBodyStruct& Two) {
					return One.Name > Two.Name;
				});
				break;
			}
			break;

		case ESortType::VE_Rarity:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FBodyStruct& One, const FBodyStruct& Two) {
					return One.Rarity < Two.Rarity;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FBodyStruct& One, const FBodyStruct& Two) {
					return One.Rarity > Two.Rarity;
				});
				break;
			}
			break;
		}
		for (size_t i = 0; i < Temp.Max(); i++)
		{
			Ret.Add(Temp[i].ID);
		}
		break;
		// body sort End ******************************************************************
	}
	case ETabEnum::VE_Wheel:
	{
		// Wheel sort start -----------------------------------------------------------
		TArray<FWheelStruct> Temp;
		for (size_t i = 0; i < Items.Max(); i++)
		{
			Temp.Add(GetWheelByID(Items[i]));
		}
		switch (SortType)
		{
		case ESortType::VE_AlphaNumeric:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FWheelStruct& One, const FWheelStruct& Two) {
					return One.Name < Two.Name;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FWheelStruct& One, const FWheelStruct& Two) {
					return One.Name > Two.Name;
				});
				break;
			}
			break;

		case ESortType::VE_Rarity:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FWheelStruct& One, const FWheelStruct& Two) {
					return One.Rarity < Two.Rarity;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FWheelStruct& One, const FWheelStruct& Two) {
					return One.Rarity > Two.Rarity;
				});
				break;
			}
			break;
		}
		for (size_t i = 0; i < Temp.Max(); i++)
		{
			Ret.Add(Temp[i].ID);
		}
		break;
		// Wheel sort End ******************************************************************
	}
		break;
	case ETabEnum::VE_Spark:
	{
		// Spark sort start -----------------------------------------------------------
		TArray<FSparkStruct> Temp;
		for (size_t i = 0; i < Items.Max(); i++)
		{
			Temp.Add(GetSparkByID(Items[i]));
		}
		switch (SortType)
		{
		case ESortType::VE_AlphaNumeric:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FSparkStruct& One, const FSparkStruct& Two) {
					return One.Name < Two.Name;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FSparkStruct& One, const FSparkStruct& Two) {
					return One.Name > Two.Name;
				});
				break;
			}
			break;

		case ESortType::VE_Rarity:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FSparkStruct& One, const FSparkStruct& Two) {
					return One.Rarity < Two.Rarity;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FSparkStruct& One, const FSparkStruct& Two) {
					return One.Rarity > Two.Rarity;
				});
				break;
			}
			break;
		}
		for (size_t i = 0; i < Temp.Max(); i++)
		{
			Ret.Add(Temp[i].ID);
		}
		break;
		// Spark sort End ******************************************************************
	}
		break;
	case ETabEnum::VE_Trail:
	{
		// Trail sort start -----------------------------------------------------------
		TArray<FTrailStruct> Temp;
		for (size_t i = 0; i < Items.Max(); i++)
		{
			Temp.Add(GetTrailByID(Items[i]));
		}
		switch (SortType)
		{
		case ESortType::VE_AlphaNumeric:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FTrailStruct& One, const FTrailStruct& Two) {
					return One.Name < Two.Name;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FTrailStruct& One, const FTrailStruct& Two) {
					return One.Name > Two.Name;
				});
				break;
			}
			break;

		case ESortType::VE_Rarity:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FTrailStruct& One, const FTrailStruct& Two) {
					return One.Rarity < Two.Rarity;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FTrailStruct& One, const FTrailStruct& Two) {
					return One.Rarity > Two.Rarity;
				});
				break;
			}
			break;
		}
		for (size_t i = 0; i < Temp.Max(); i++)
		{
			Ret.Add(Temp[i].ID);
		}
		break;
		// Trail sort End ******************************************************************
	}
		break;
	case ETabEnum::VE_Poof:
	{
		// Poof sort start -----------------------------------------------------------
		TArray<FPoofStruct> Temp;
		for (size_t i = 0; i < Items.Max(); i++)
		{
			Temp.Add(GetPoofByID(Items[i]));
		}
		switch (SortType)
		{
		case ESortType::VE_AlphaNumeric:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FPoofStruct& One, const FPoofStruct& Two) {
					return One.Name < Two.Name;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FPoofStruct& One, const FPoofStruct& Two) {
					return One.Name > Two.Name;
				});
				break;
			}
			break;

		case ESortType::VE_Rarity:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FPoofStruct& One, const FPoofStruct& Two) {
					return One.Rarity < Two.Rarity;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FPoofStruct& One, const FPoofStruct& Two) {
					return One.Rarity > Two.Rarity;
				});
				break;
			}
			break;
		}
		for (size_t i = 0; i < Temp.Max(); i++)
		{
			Ret.Add(Temp[i].ID);
		}
		break;
		// Poof sort End ******************************************************************
	}
		break;
	case ETabEnum::VE_Trick:
	{
		// Trick sort start -----------------------------------------------------------
		TArray<FTrickStruct> Temp;
		for (size_t i = 0; i < Items.Max(); i++)
		{
			Temp.Add(GetTrickByID(Items[i]));
		}
		switch (SortType)
		{
		case ESortType::VE_AlphaNumeric:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FTrickStruct& One, const FTrickStruct& Two) {
					return One.Name < Two.Name;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FTrickStruct& One, const FTrickStruct& Two) {
					return One.Name > Two.Name;
				});
				break;
			}
			break;

		case ESortType::VE_Rarity:

			switch (Direction)
			{
			case EDirection::VE_Ascending:
				Temp.Sort([](const FTrickStruct& One, const FTrickStruct& Two) {
					return One.Rarity < Two.Rarity;
				});
				break;
			case EDirection::VE_Descending:
				Temp.Sort([](const FTrickStruct& One, const FTrickStruct& Two) {
					return One.Rarity > Two.Rarity;
				});
				break;
			}
			break;
		}
		for (size_t i = 0; i < Temp.Max(); i++)
		{
			Ret.Add(Temp[i].ID);
		}
		break;
		// Trick sort End ******************************************************************
	}
		break;
	}

	return Ret;
}
