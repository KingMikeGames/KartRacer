// Fill out your copyright notice in the Description page of Project Settings.

#include "KartRacer.h"
#include "PlayerData.h"

UPlayerData::UPlayerData() :
	PlayerName("MoonBeef"),
	PlayerLevel(1),
	TrueSkill(10000),
	WinStreak(0),
	ExperiencePoints(0),
	ExpMultiplier(1)
{

}

int32 UPlayerData::AddExperience(int32 points)
{
	ExperiencePoints += points * ExpMultiplier;

	if (ExperiencePoints >= 1000)
	{
		LevelUp();
	}
	return ExperiencePoints;
}

int32 UPlayerData::LevelUp()
{
	PlayerLevel++;
	ExperiencePoints -= 1000;
	return PlayerLevel;
}
