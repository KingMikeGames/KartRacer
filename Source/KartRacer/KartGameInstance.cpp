// Fill out your copyright notice in the Description page of Project Settings.

#include "KartRacer.h"
#include "KartGameInstance.h"


UKartGameInstance::UKartGameInstance()
{

}

FBodyStruct UKartGameInstance::GetBodyByID(int32 ID)
{
	return BodyDB[ID];
}

FWheelStruct UKartGameInstance::GetWheelByID(int32 ID)
{
	return WheelDB[ID];
}

FPoofStruct UKartGameInstance::GetPoofByID(int32 ID)
{
	return PoofDB[ID];
}

FTrailStruct UKartGameInstance::GetTrailByID(int32 ID)
{
	return TrailDB[ID];
}

FTrickStruct UKartGameInstance::GetTrickByID(int32 ID)
{
	return TrickDB[ID];
}

FSparkStruct UKartGameInstance::GetSparkByID(int32 ID)
{
	return SparkDB[ID];
}

TArray<int32> UKartGameInstance::SortInventory(TArray<int32> Items, ETabEnum Type, ESortType SortType, EDirection Direction)
{
	TArray<int32> Ret;

	switch (Type)
	{
	case ETabEnum::VE_Body:
	{
		// body sort start -----------------------------------------------------------
		TArray<FBodyStruct> Temp;
		for (size_t i = 0; i < Items.Num(); i++)
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
		for (size_t i = 0; i < Temp.Num(); i++)
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
		for (size_t i = 0; i < Items.Num(); i++)
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
		for (size_t i = 0; i < Temp.Num(); i++)
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
		for (size_t i = 0; i < Items.Num(); i++)
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
		for (size_t i = 0; i < Temp.Num(); i++)
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
		for (size_t i = 0; i < Items.Num(); i++)
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
		for (size_t i = 0; i < Temp.Num(); i++)
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
		for (size_t i = 0; i < Items.Num(); i++)
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
		for (size_t i = 0; i < Temp.Num(); i++)
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
		for (size_t i = 0; i < Items.Num(); i++)
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
		for (size_t i = 0; i < Temp.Num(); i++)
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

TArray<int32> UKartGameInstance::GetInventory(ETabEnum Tab)
{
	switch (Tab)
	{
	case ETabEnum::VE_Body:
		return PlayerInfo.Inventory.BodyInventory;
		break;
	case ETabEnum::VE_Wheel:
		return PlayerInfo.Inventory.WheelInventory;
		break;
	case ETabEnum::VE_Spark:
		return PlayerInfo.Inventory.SparkInventory;
		break;
	case ETabEnum::VE_Trail:
		return PlayerInfo.Inventory.TrailInventory;
		break;
	case ETabEnum::VE_Poof:
		return PlayerInfo.Inventory.PoofInventory;
		break;
	case ETabEnum::VE_Trick:
		return PlayerInfo.Inventory.TrickInventory;
		break;
	default:
		return PlayerInfo.Inventory.BodyInventory;
		break;
	}

}


int32 UKartGameInstance::AddExperience(int32 points)
{
	PlayerInfo.ExperiencePoints += points * PlayerInfo.ExpMultiplier;

	if (PlayerInfo.ExperiencePoints >= 1000)
	{
		LevelUp();
	}
	return PlayerInfo.ExperiencePoints;
}

int32 UKartGameInstance::LevelUp()
{
	PlayerInfo.PlayerLevel++;
	PlayerInfo.ExperiencePoints -= 1000;
	return PlayerInfo.PlayerLevel;
}

void UKartGameInstance::ChangeEquipment(ETabEnum Type, int ID)
{

	ChangedEquipment = Type;
	EquipmentHasChanged = true;

	switch (Type)
	{
	case ETabEnum::VE_Body:
		PlayerInfo.CurrentlyEquipped.Body = ID;
		break;
	case ETabEnum::VE_Wheel:
		PlayerInfo.CurrentlyEquipped.Wheel = ID;
		break;
	case ETabEnum::VE_Spark:
		PlayerInfo.CurrentlyEquipped.Spark = ID;
		break;
	case ETabEnum::VE_Trail:
		PlayerInfo.CurrentlyEquipped.Trail = ID;
		break;
	case ETabEnum::VE_Poof:
		PlayerInfo.CurrentlyEquipped.Poof = ID;
		break;
	case ETabEnum::VE_Trick:
		PlayerInfo.CurrentlyEquipped.Trick = ID;
		break;
	default:
		break;
	}
}
