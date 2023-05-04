#include "PrecompileHeader.h"
#include "StageMap.h"
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineSerializer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

StageMap* StageMap::MainStageMap = nullptr;

StageMap::StageMap()
{
	MainStageMap = this;
}

StageMap::~StageMap()
{

}

std::list<float4>& StageMap::GetMonsterPath(int _Index)
{
	return MonsterPath[_Index];
}

void StageMap::Start()
{
	StageMapRenderer = CreateComponent<GameEngineSpriteRenderer>();
	StageMapRenderer->SetPipeLine("2DTexture");
	StageMapRenderer->SetTexture("Stage_1.png");
	StageMapRenderer->GetTransform()->SetWorldScale(StageMapRendererScale);

	MonsterPath.resize(MonsterPathCount);

	LoadMonsterPath();
}

void StageMap::Update(float _DeltaTime)
{

}

void StageMap::Render(float _DeltaTime)
{

}

void StageMap::LoadMonsterPath()
{

	GameEngineSerializer Serial;
	Serial.BufferResize(3000);
	GameEngineFile File("..//ContentsData//Stage1PathData.txt");
	File.LoadBin(Serial);

	int ListSize = 0;

	for (size_t i = 0; i < MonsterPath.size(); i++)
	{
		Serial.Read(ListSize);

		for (size_t j = 0; j < ListSize; j++)
		{
			MonsterPath[i].emplace_back();
		}

		for (float4& k : MonsterPath[i])
		{
			Serial.Read(&k, sizeof(float4));
		}
	}
}
