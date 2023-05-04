#include "PrecompileHeader.h"
#include "BaseMonster.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "StageMap.h"


BaseMonster::BaseMonster()
{

}

BaseMonster::~BaseMonster()
{

}

void BaseMonster::Start()
{
	GetTransform()->SetWorldPosition(ActorPos);
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>();
	MonsterRenderer->SetPipeLine("2DTexture");
	MonsterRenderer->SetTexture("DesertThug0000.png");
	MonsterRenderer->GetTransform()->SetWorldScale({66,56});
	

	AcStageMap = StageMap::MainStageMap;

}

void BaseMonster::Update(float _DeltaTime)
{
	if (GameEngineInput::IsPress("RightClick"))
	{

		WalkPath(_DeltaTime);
	}
}

void BaseMonster::WalkToNextPoint(float _DeltaTime)
{
	//내가 점을 어떻게 찍던 상관 없이 속도는 일정해야한다...
	//기준 속력 V = 100 가정 (1초에 100을 간다는 뜻)
	//길이가 L = 200 일때 Time*0.5 = Time * (V/L)
	//길이가 100 일때 Time*1 = Time * (V/L)
	//길이가 50 일때 Time*2 = Time * (V/L)
	//길이가 25 일때 Time*4 = Time * (V/L)

	Time += _DeltaTime;
	Ratio = Time * (Speed / (*NextPoint - *CurPoint).Size());
	ActorPos = float4::LerpClamp(*CurPoint, *NextPoint, Ratio);
	GetTransform()->SetWorldPosition(ActorPos);
}

void BaseMonster::WalkPath(float _DeltaTime)
{
	if (PathInfo == nullptr)
	{
		PathInfo = &(AcStageMap->GetMonsterPath(0));
		CurPoint = PathInfo->begin();
		NextPoint = ++(PathInfo->begin());
	}

	if (Ratio >= 1)
	{
		Time = 0;
		Ratio = 0;
		CurPoint++;
		NextPoint++;
	}

	if (NextPoint == PathInfo->end())
	{
		Death();
		return;
	}

	WalkToNextPoint(_DeltaTime);
}
