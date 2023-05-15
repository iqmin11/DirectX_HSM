#include "PrecompileHeader.h"
#include "BaseMonster.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "DesertThug.h"
#include "DuneRaider.h"

std::list<std::shared_ptr<BaseMonster>> BaseMonster::LiveMonsterList = std::list<std::shared_ptr<BaseMonster>>();

BaseMonster::BaseMonster()
{

}

BaseMonster::~BaseMonster()
{

}

std::shared_ptr<BaseMonster> BaseMonster::CreateMonster(const std::shared_ptr<GameEngineLevel> _Level, const MonsterEnum _Monster, std::vector<float4>& _PathInfo)
{
	std::shared_ptr<BaseMonster> Result = nullptr;
	switch (_Monster)
	{
	case MonsterEnum::DesertThug:
		Result = _Level->CreateActor<DesertThug>(static_cast<int>(ActorOrder::Monster));
		Result->SetPathInfo(_PathInfo);
		return Result;
		break;
	case MonsterEnum::DuneRaider:
		Result = _Level->CreateActor<DuneRaider>(static_cast<int>(ActorOrder::Monster));
		Result->SetPathInfo(_PathInfo);
		return Result;
		break;
	default:
		MsgAssert("�̱���");
		break;
	}
	return nullptr;
}

void BaseMonster::Start()
{
	//GetTransform()->SetWorldPosition(ActorPos);
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>();
	MonsterCol = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::Monster));
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
		LiveMonsterListRelease();
		return;
	}

	WalkToNextPoint(_DeltaTime);
}

void BaseMonster::LiveMonsterListRelease()
{
	std::list<std::shared_ptr<BaseMonster>>::iterator ReleaseStartIter = LiveMonsterList.begin();
	std::list<std::shared_ptr<BaseMonster>>::iterator ReleaseEndIter = LiveMonsterList.end();

	for (; ReleaseStartIter != ReleaseEndIter; )
	{
		std::shared_ptr<BaseMonster>& Object = *ReleaseStartIter;

		if (false == Object->IsDeath())
		{
			++ReleaseStartIter;
			continue;
		}

		ReleaseStartIter = LiveMonsterList.erase(ReleaseStartIter);
	}
}


