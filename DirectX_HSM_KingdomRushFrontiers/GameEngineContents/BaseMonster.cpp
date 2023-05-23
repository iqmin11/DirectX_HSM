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
		Result = _Level->CreateActor<DesertThug>(ActorOrder::Monster);
		break;
	case MonsterEnum::DuneRaider:
		Result = _Level->CreateActor<DuneRaider>(ActorOrder::Monster);
		break;
	default:
		MsgAssert("미구현");
		break;
	}

	Result->SetPathInfo(_PathInfo);
	return Result;
}


void BaseMonster::Start()
{
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	MonsterCol = CreateComponent<GameEngineCollision>(ColOrder::Monster); 
	LifeBarBg = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	LifeBarBg->SetTexture("lifebar_bg_small.png");
	LifeBarBg->GetTransform()->SetWorldScale(LifeBarScale);
	LifeBarBg->GetTransform()->SetLocalPosition(LifeBarLocalPos);
	LifeBar = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	LifeBar->SetTexture("lifebar_small.png");
	LifeBar->GetTransform()->SetWorldScale(LifeBarScale);
	LifeBar->GetTransform()->SetLocalPosition(LifeBarLocalPos);
}

void BaseMonster::Update(float _DeltaTime)
{
	WalkPath(_DeltaTime);
	CalMonsterDir();
	if (CurHP <= 0)
	{
		Death();
		return;
	}
	UpdateLiveBar();
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
	Ratio = Time * (Data.Speed / (*NextPoint - *CurPoint).Size());
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

void BaseMonster::CalMonsterDir()
{
	ActorDir.w = 0.0f;
	ActorDir = ActorPos - PrevActorPos;
	ActorDir.Normalize();
	PrevActorPos = ActorPos;
}

void BaseMonster::UpdateLiveBar()
{
	float4 CurHpBarXSize = float4::LerpClamp(float4{ 0,LifeBarScale.y,0,1 }, float4{ LifeBarScale.x,LifeBarScale.y,0,1 }, CurHP / Data.Hp);
	float4 CurHpBarXPos = float4::LerpClamp(float4{ -LifeBarScale.hx(),LifeBarLocalPos.y,0,1 }, float4{ 0,LifeBarLocalPos.y,0,1 }, CurHP / Data.Hp);
	LifeBar->GetTransform()->SetWorldScale(CurHpBarXSize);
	LifeBar->GetTransform()->SetLocalPosition(CurHpBarXPos);
}

float BaseMonster::CalDistance()
{
	return (*LastPoint - ActorPos).Size();
}


