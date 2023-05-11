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