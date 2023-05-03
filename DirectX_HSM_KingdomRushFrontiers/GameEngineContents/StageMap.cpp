#include "PrecompileHeader.h"
#include "StageMap.h"
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineSerializer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

//StageMap* StageMap::MainStageMap = nullptr;

StageMap::StageMap()
{
	//MainStageMap = this;
}

StageMap::~StageMap()
{

}

std::list<float4>& StageMap::GetMonsterPath(int _Index)
{
	if (MonsterPaths.find(_Index) == MonsterPaths.end())
	{
		MsgAssert("해당 몬스터 침투 경로를 찾을 수 없습니다");
	}
	return MonsterPaths.find(_Index)->second;
}

void StageMap::Start()
{
	StageMapRenderer = CreateComponent<GameEngineSpriteRenderer>();
	StageMapRenderer->SetPipeLine("2DTexture");
	StageMapRenderer->SetTexture("Stage_1.png");
	StageMapRenderer->GetTransform()->SetWorldScale(StageMapRendererScale);

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
	/*GameEngineSerializer Serial;
	GameEngineFile File("..//ContentsData//Stage1MapData.txt");
	File.LoadBin(Serial);

	int ListSize = 0;
	Serial.Read(ListSize);

	for (size_t i = 0; i < ListSize; i++)
	{
		TestPath.emplace_back();
	}

	for (float4& i : TestPath)
	{
		Serial.Read(&i, sizeof(float4));
	}*/
}
