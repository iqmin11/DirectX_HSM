#pragma once
#include "ContentsEnum.h"

class LinePath
{
public:
	std::vector<float4> Points = std::vector<float4>();
};

class MonsterSpawnData
{
public:
	MonsterSpawnData() {}
	MonsterSpawnData(MonsterEnum _Monster, int _LineIndex, float _StartTime)
		: Monster(_Monster), LineIndex(_LineIndex), StartTime(_StartTime) {}
public:
	MonsterEnum Monster = MonsterEnum::Null;
	int LineIndex = 0;
	float StartTime = 0;
};

class WaveData
{
public:
	std::vector<MonsterSpawnData> MonsterSpawn;
};

class MonsterData
{
public:
	MonsterEnum Monster = MonsterEnum::Null;
	int Hp = 0;
	int Speed = 0;
};

class StageData
{
public:
	//int StageLevel = 0;
	//std::string BackGroundName = "\0";
	std::vector<LinePath> Lines = std::vector<LinePath>();
	std::vector<WaveData> Waves = std::vector<WaveData>();
	std::vector<float4> BuildAreaPos = std::vector<float4>();
};

class TowerData
{
public:
	//static const float 180.f;
	//static const float 190.f;
	//static const float 220.f;
	//static const float 245.f;
	//static const float 270.f;

	void SetData(TowerEnum _Enum)
	{
		switch (_Enum)
		{
		case TowerEnum::Null:
			break;
		case TowerEnum::RangedTower_Level1:
			TowerType = TowerEnum::RangedTower_Level1;
			Level = 1;
			FireRate = 0.8f;
			Range = 190.f;
			Damage_min = 4.0f;
			Damage_MAX = 6.0f;
			break;
		case TowerEnum::RangedTower_Level2:
			TowerType = TowerEnum::RangedTower_Level2;
			Level = 2;
			FireRate = 0.6f;
			Range = 220.f;
			Damage_min = 7.0f;
			Damage_MAX = 11.0f;
			break;
		case TowerEnum::RangedTower_Level3:
			TowerType = TowerEnum::RangedTower_Level3;
			Level = 3;
			FireRate = 0.5f;
			Range = 245.f;
			Damage_min = 10.0f;
			Damage_MAX = 16.0f;
			break;
		case TowerEnum::RangedTower_Level4:
			TowerType = TowerEnum::RangedTower_Level4;
			Level = 4;
			FireRate = 0.5f;
			Range = 270.f;
			Damage_min = 15.0f;
			Damage_MAX = 23.0f;
			break;
		case TowerEnum::MeleeTower_Level1:
			TowerType = TowerEnum::MeleeTower_Level1;
			Level = 1;
			FireRate = 1.0f;
			Range = 0.0f;
			Damage_min = 1.0f;
			Damage_MAX = 3.0f;
			break;
		case TowerEnum::MeleeTower_Level2:
			TowerType = TowerEnum::MeleeTower_Level2;
			Level = 2;
			FireRate = 1.6f;
			Range = 0.0f;
			Damage_min = 3.0f;
			Damage_MAX = 4.0f;
			break;
		case TowerEnum::MeleeTower_Level3:
			TowerType = TowerEnum::MeleeTower_Level3;
			Level = 3;
			FireRate = 1.6f;
			Range = 0.0f;
			Damage_min = 6.0f;
			Damage_MAX = 10.0f;
			break;
		case TowerEnum::MeleeTower_Level4:
			TowerType = TowerEnum::MeleeTower_Level4;
			Level = 4;
			FireRate = 1.0f;
			Range = 0.0f;
			Damage_min = 10.0f;
			Damage_MAX = 14.0f;
			break;
		case TowerEnum::MagicTower_Level1:
			TowerType = TowerEnum::MagicTower_Level1;
			Level = 1;
			FireRate = 1.5f;
			Range = 180.f;
			Damage_min = 9.0f;
			Damage_MAX = 17.0f;
			break;
		case TowerEnum::MagicTower_Level2:
			TowerType = TowerEnum::MagicTower_Level2;
			Level = 2;
			FireRate = 1.5f;
			Range = 190.f;
			Damage_min = 23.0f;
			Damage_MAX = 43.0f;
			break;
		case TowerEnum::MagicTower_Level3:
			TowerType = TowerEnum::MagicTower_Level3;
			Level = 3;
			FireRate = 1.5f;
			Range = 220.f;
			Damage_min = 40.0f;
			Damage_MAX = 74.0f;
			break;
		case TowerEnum::MagicTower_Level4:
			TowerType = TowerEnum::MagicTower_Level4;
			Level = 4;
			FireRate = 1.5f;
			Range = 245.f;
			Damage_min = 60.0f;
			Damage_MAX = 120.0f;
			break;
		case TowerEnum::ArtilleryTower_Level1:
			TowerType = TowerEnum::ArtilleryTower_Level1;
			Level = 1;
			FireRate = 3.0f;
			Range = 190.f;
			Damage_min = 8.0f;
			Damage_MAX = 15.0f;
			break;
		case TowerEnum::ArtilleryTower_Level2:
			TowerType = TowerEnum::ArtilleryTower_Level2;
			Level = 2;
			FireRate = 3.0f;
			Range = 190.f;
			Damage_min = 20.0f;
			Damage_MAX = 40.0f;
			break;
		case TowerEnum::ArtilleryTower_Level3:
			TowerType = TowerEnum::ArtilleryTower_Level3;
			Level = 3;
			FireRate = 3.0f;
			Range = 220.f;
			Damage_min = 30.0f;
			Damage_MAX = 60.0f;
			break;
		case TowerEnum::ArtilleryTower_Level4:
			TowerType = TowerEnum::ArtilleryTower_Level4;
			Level = 4;
			FireRate = 3.0f;
			Range = 220.f;
			Damage_min = 25.0f;
			Damage_MAX = 45.0f;
			break;
		default:
			break;
		}
	}

public:
	TowerEnum TowerType = TowerEnum::Null;
	int Level = 0;
	float FireRate = 0.0f;
	float Range = 0.0f;
	float Damage_min = 0.0f;
	float Damage_MAX = 0.0f;
};

//const float TowerData::180.f = 180.f;
//const float TowerData::190.f = 190.f;
//const float TowerData::220.f = 220.f;
//const float TowerData::245.f = 245.f;
//const float TowerData::270.f = 270.f;
