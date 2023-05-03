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
	switch (_Index)
	{
	case 0:
		return MonsterPath0;
	case 1:
		return MonsterPath1;
	case 2:
		return MonsterPath2;
	case 3:
		return MonsterPath3;
	case 4:
		return MonsterPath4;
	case 5:
		return MonsterPath5;
	default:
		break;
	}
}

void StageMap::Start()
{
	StageMapRenderer = CreateComponent<GameEngineSpriteRenderer>();
	StageMapRenderer->SetPipeLine("2DTexture");
	StageMapRenderer->SetTexture("Stage_1.png");
	StageMapRenderer->GetTransform()->SetWorldScale(StageMapRendererScale);

	LoadMonsterPath();

	//GameEngineSerializer Serial;
	//GameEngineFile File("..//ContentsSave//Stage1SaveMonsterPath0.txt");
	//File.LoadBin(Serial);
	
	//int ListSize = Serial.Read();
	////Read
	//
	//for (size_t i = 0; i < Serial.GetBufferSize(); i++)
	//{
	//	TestPath.emplace_back();
	//	
	//	Serial.Read(&TestPath,sizeof(float4));
	//}


	//RedDot = CreateComponent<GameEngineRenderer>();
	//RedDot->SetPipeLine("2DTexture");
	//RedDot->GetTransform()->SetWorldScale({10,10});
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
	GameEngineFile File("..//ContentsData//Stage1PathData.txt");
	File.LoadBin(Serial);

	int ListSize = 0;
	Serial.Read(ListSize);

	for (size_t i = 0; i < ListSize; i++)
	{
		MonsterPath0.emplace_back();
	}

	for (float4& i : MonsterPath0)
	{
		Serial.Read(&i, sizeof(float4));
	}

	Serial.Read(ListSize);

	for (size_t i = 0; i < ListSize; i++)
	{
		MonsterPath1.emplace_back();
	}

	for (float4& i : MonsterPath1)
	{
		Serial.Read(&i, sizeof(float4));
	}

	Serial.Read(ListSize);

	for (size_t i = 0; i < ListSize; i++)
	{
		MonsterPath2.emplace_back();
	}

	for (float4& i : MonsterPath2)
	{
		Serial.Read(&i, sizeof(float4));
	}

	Serial.Read(ListSize);

	for (size_t i = 0; i < ListSize; i++)
	{
		MonsterPath3.emplace_back();
	}

	for (float4& i : MonsterPath3)
	{
		Serial.Read(&i, sizeof(float4));
	}

	Serial.Read(ListSize);

	for (size_t i = 0; i < ListSize; i++)
	{
		MonsterPath4.emplace_back();
	}

	for (float4& i : MonsterPath4)
	{
		Serial.Read(&i, sizeof(float4));
	}

	Serial.Read(ListSize);

	for (size_t i = 0; i < ListSize; i++)
	{
		MonsterPath5.emplace_back();
	}

	for (float4& i : MonsterPath5)
	{
		Serial.Read(&i, sizeof(float4));
	}
}
