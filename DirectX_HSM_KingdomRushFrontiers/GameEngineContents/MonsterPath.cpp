#include "PrecompileHeader.h"
#include "MonsterPath.h"
#include <GameEngineBase/GameEngineSerializer.h>

MonsterPath::MonsterPath()
{

}

MonsterPath::~MonsterPath()
{

}

void MonsterPath::Start()
{
	MonsterPathVec.resize(MonsterPathCount);
	LoadMonsterPath();
}

void MonsterPath::Update(float _DeltaTime)
{
}

void MonsterPath::LoadMonsterPath()
{
	GameEngineSerializer Serial;
	Serial.BufferResize(3000);
	GameEngineFile File("..//ContentsData//Stage1PathData.txt");
	File.LoadBin(Serial);

	int ListSize = 0;

	for (size_t i = 0; i < MonsterPathVec.size(); i++)
	{
		Serial.Read(ListSize);

		for (size_t j = 0; j < ListSize; j++)
		{
			MonsterPathVec[i].emplace_back();
		}

		for (float4& k : MonsterPathVec[i])
		{
			Serial.Read(&k, sizeof(float4));
		}
	}
}
