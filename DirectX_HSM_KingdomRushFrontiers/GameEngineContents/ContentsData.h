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
	std::vector<MonsterData> MonsterData;
};

class TowerData
{
public:
	void SetData(TowerEnum _Enum)
	{
		switch (_Enum)
		{
		case TowerEnum::Null:
			break;
		case TowerEnum::RangedTower_Level1:
			TowerType = TowerEnum::RangedTower_Level1;
			FireRate = 0.8f;
			Range = 190.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 4.0f;
			Damage_MAX = 6.0f;
			break;
		case TowerEnum::RangedTower_Level2:
			TowerType = TowerEnum::RangedTower_Level2;
			FireRate = 0.6f;
			Range = 220.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 7.0f;
			Damage_MAX = 11.0f;
			break;
		case TowerEnum::RangedTower_Level3:
			TowerType = TowerEnum::RangedTower_Level3;
			FireRate = 0.5f;
			Range = 245.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 10.0f;
			Damage_MAX = 16.0f;
			break;
		case TowerEnum::RangedTower_Level4:
			TowerType = TowerEnum::RangedTower_Level4;
			FireRate = 0.5f;
			Range = 270.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 15.0f;
			Damage_MAX = 23.0f;
			break;
		case TowerEnum::MeleeTower_Level1:
			TowerType = TowerEnum::MeleeTower_Level1;
			FireRate = 1.0f;
			Range = 0.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 1.0f;
			Damage_MAX = 3.0f;
			break;
		case TowerEnum::MeleeTower_Level2:
			TowerType = TowerEnum::MeleeTower_Level2;
			FireRate = 1.6f;
			Range = 0.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 3.0f;
			Damage_MAX = 4.0f;
			break;
		case TowerEnum::MeleeTower_Level3:
			TowerType = TowerEnum::MeleeTower_Level3;
			FireRate = 1.6f;
			Range = 0.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 6.0f;
			Damage_MAX = 10.0f;
			break;
		case TowerEnum::MeleeTower_Level4:
			TowerType = TowerEnum::MeleeTower_Level4;
			FireRate = 1.0f;
			Range = 0.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 10.0f;
			Damage_MAX = 14.0f;
			break;
		case TowerEnum::MagicTower_Level1:
			TowerType = TowerEnum::MagicTower_Level1;
			FireRate = 1.5f;
			Range = 180.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 9.0f;
			Damage_MAX = 17.0f;
			break;
		case TowerEnum::MagicTower_Level2:
			TowerType = TowerEnum::MagicTower_Level2;
			FireRate = 1.5f;
			Range = 190.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 23.0f;
			Damage_MAX = 43.0f;
			break;
		case TowerEnum::MagicTower_Level3:
			TowerType = TowerEnum::MagicTower_Level3;
			FireRate = 1.5f;
			Range = 220.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 40.0f;
			Damage_MAX = 74.0f;
			break;
		case TowerEnum::MagicTower_Level4:
			TowerType = TowerEnum::MagicTower_Level4;
			FireRate = 1.5f;
			Range = 245.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 60.0f;
			Damage_MAX = 120.0f;
			break;
		case TowerEnum::ArtilleryTower_Level1:
			TowerType = TowerEnum::ArtilleryTower_Level1;
			FireRate = 3.0f;
			Range = 190.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 8.0f;
			Damage_MAX = 15.0f;
			break;
		case TowerEnum::ArtilleryTower_Level2:
			TowerType = TowerEnum::ArtilleryTower_Level2;
			FireRate = 3.0f;
			Range = 190.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 20.0f;
			Damage_MAX = 40.0f;
			break;
		case TowerEnum::ArtilleryTower_Level3:
			TowerType = TowerEnum::ArtilleryTower_Level3;
			FireRate = 3.0f;
			Range = 220.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 30.0f;
			Damage_MAX = 60.0f;
			break;
		case TowerEnum::ArtilleryTower_Level4:
			TowerType = TowerEnum::ArtilleryTower_Level4;
			FireRate = 3.0f;
			Range = 220.0f; //short 180, average 190, long 220, greate 245, extream 270
			Damage_min = 25.0f;
			Damage_MAX = 45.0f;
			break;
		default:
			break;
		}
	}

public:
	TowerEnum TowerType = TowerEnum::Null;
	float FireRate = 0.0f;
	float Range = 0.0f; //short 180, average 190, long 220, greate 245, extream 270
	float Damage_min = 0.0f;
	float Damage_MAX = 0.0f;
};
