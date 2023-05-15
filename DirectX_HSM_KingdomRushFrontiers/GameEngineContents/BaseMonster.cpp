#include "PrecompileHeader.h"
#include "BaseMonster.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "DesertThug.h"
#include "DuneRaider.h"


BaseMonster::BaseMonster()
{

}

BaseMonster::~BaseMonster()
{

}

void BaseMonster::CreateMonster(const std::shared_ptr<GameEngineLevel> _Level, const MonsterEnum _Monster, std::vector<float4>& _PathInfo)
{
	switch (_Monster)
	{
	case MonsterEnum::DesertThug:
		_Level->CreateActor<DesertThug>(static_cast<int>(ActorOrder::Monster))->SetPathInfo(_PathInfo);
		break;
	case MonsterEnum::DuneRaider:
		_Level->CreateActor<DuneRaider>(static_cast<int>(ActorOrder::Monster))->SetPathInfo(_PathInfo);
		break;
	default:
		MsgAssert("미구현");
		break;
	}
}

void BaseMonster::Start()
{
	//GetTransform()->SetWorldPosition(ActorPos);
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>();
	//MonsterRenderer->SetTexture("DesertThug0000.png");
	//MonsterRenderer->GetTransform()->SetWorldScale({66,56});
}

void BaseMonster::Update(float _DeltaTime)
{
	WalkPath(_DeltaTime);
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
		MsgAssert("몬스터의 경로가 지정되지 않아 이동할 수 없습니다.");
		return;
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


