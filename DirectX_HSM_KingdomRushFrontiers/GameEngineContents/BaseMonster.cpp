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
		MsgAssert("�̱���");
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
	//���� ���� ��� ��� ��� ���� �ӵ��� �����ؾ��Ѵ�...
	//���� �ӷ� V = 100 ���� (1�ʿ� 100�� ���ٴ� ��)
	//���̰� L = 200 �϶� Time*0.5 = Time * (V/L)
	//���̰� 100 �϶� Time*1 = Time * (V/L)
	//���̰� 50 �϶� Time*2 = Time * (V/L)
	//���̰� 25 �϶� Time*4 = Time * (V/L)

	Time += _DeltaTime;
	Ratio = Time * (Speed / (*NextPoint - *CurPoint).Size());
	ActorPos = float4::LerpClamp(*CurPoint, *NextPoint, Ratio);
	GetTransform()->SetWorldPosition(ActorPos);
}

void BaseMonster::WalkPath(float _DeltaTime)
{
	if (PathInfo == nullptr)
	{
		MsgAssert("������ ��ΰ� �������� �ʾ� �̵��� �� �����ϴ�.");
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


