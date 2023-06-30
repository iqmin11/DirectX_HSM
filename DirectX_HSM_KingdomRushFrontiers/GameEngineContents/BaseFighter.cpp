#include "PrecompileHeader.h"
#include "BaseFighter.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RallyPoint.h"
#include "BaseMonster.h"

BaseFighter::BaseFighter()
{

}

BaseFighter::~BaseFighter()
{
	if (TargetMonster != nullptr)
	{
		if (TargetMonster->TargetFighter != nullptr)
		{
			TargetMonster->TargetFighter = nullptr;
		}
		TargetMonster = nullptr;
	}
}

void BaseFighter::SetParentRally(RallyPoint* _Rally)
{
	ParentRally = _Rally;
	GetTransform()->SetParent(_Rally->GetTransform(), false);
	GetTransform()->SetWorldPosition(_Rally->GetTransform()->GetWorldPosition());
}

void BaseFighter::ResetRatio()
{
	Time = 0.f;
	Ratio = 0.f;
}

void BaseFighter::Start()
{
	FighterRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);

	FighterCol = CreateComponent<GameEngineCollision>(ColOrder::Fighter);
	FighterCol->GetTransform()->SetWorldScale(ColScale);
	FighterCol->GetTransform()->SetLocalPosition(ColLocalPos);

	LifeBarBg = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	LifeBarBg->SetTexture("lifebar_bg_small.png");
	LifeBarBg->GetTransform()->SetWorldScale(LifeBarScale);
	LifeBarBg->GetTransform()->SetLocalPosition(LifeBarLocalPos);
	LifeBar = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	LifeBar->SetTexture("lifebar_small.png");
	LifeBar->GetTransform()->SetWorldScale(LifeBarScale);
	LifeBar->GetTransform()->SetLocalPosition(LifeBarLocalPos);
}

void BaseFighter::Update(float _DeltaTime)
{
	if (ParentRally == nullptr)
	{
		MsgAssert("Fighter의 부모 랠리포인트가 설정되지 않았습니다.")
	}

	//if (ParentRally->IsDeath())
	//{
	//	Death();
	//}

	UpdateLifeBar();
}



void BaseFighter::MoveToRally(float _DeltaTime)
{
	float4 test = GetTransform()->GetWorldPosition();
	float4 RallyPos = RallyTransform->GetWorldPosition();
	Time += _DeltaTime;
	Ratio = Time * (Speed / (RallyPos - PrevPos).Size());
	ActorPos = float4::LerpClamp(PrevPos, RallyPos, Ratio);
	GetTransform()->SetWorldPosition(ActorPos);

	if (ActorPos.x - RallyPos.x > 0)
	{
		FighterRenderer->GetTransform()->SetLocalNegativeScaleX();
	}
	else if (ActorPos.x - RallyPos.x < 0)
	{
		FighterRenderer->GetTransform()->SetLocalPositiveScaleX();
	}

	if (Ratio >= 1)
	{
		State = FighterState::Idle;
	}
}

void BaseFighter::ReturnToRally(float _DeltaTime)
{
	float4 RallyPos = RallyTransform->GetWorldPosition();
	Time += _DeltaTime;

	Ratio = Time * (Speed / (RallyPos - SavePos).Size());
	ActorPos = float4::LerpClamp(SavePos, RallyPos, Ratio);
	GetTransform()->SetWorldPosition(ActorPos);
	//if (Ratio >= 1.f)
	//{
	//	State = FighterState::Idle;
	//}

	if (ActorPos.x - RallyPos.x > 0)
	{
		FighterRenderer->GetTransform()->SetLocalNegativeScaleX();
	}
	else if (ActorPos.x - RallyPos.x < 0)
	{
		FighterRenderer->GetTransform()->SetLocalPositiveScaleX();
	}
}

void BaseFighter::MoveToTarget(float _DeltaTime)
{
	if (TargetMonster->State != MonsterState::Idle)
	{
		TargetMonster->State = MonsterState::Idle;
	}

	Time += _DeltaTime;
	float4 TargetPos = TargetMonster->GetTransform()->GetWorldPosition();
	if (SavePos != float4::Null)
	{
		Ratio = Time * (Speed / (TargetPos - SavePos).Size());
		ActorPos = float4::LerpClamp(SavePos, TargetPos, Ratio);
	}
	else
	{
		Ratio = Time * (Speed / (TargetPos - PrevPos).Size());
		ActorPos = float4::LerpClamp(PrevPos, TargetPos, Ratio);
	}

	if (ActorPos.x - TargetPos.x > 0)
	{
		FighterRenderer->GetTransform()->SetLocalNegativeScaleX();
	}
	else if (ActorPos.x - TargetPos.x < 0)
	{
		FighterRenderer->GetTransform()->SetLocalPositiveScaleX();
	}

	GetTransform()->SetWorldPosition(ActorPos);
	if (FighterCol->GetTransform()->Collision({._OtherTrans = TargetMonster->GetMonsterCol()->GetTransform(), .ThisType = ColType::SPHERE2D, .OtherType = ColType::SPHERE2D}))
	{
		State = FighterState::Attack;
		SavePos = GetTransform()->GetWorldPosition();
	}
}

void BaseFighter::UpdateLifeBar()
{
	float4 CurHpBarXSize = float4::LerpClamp(float4{ 0,LifeBarScale.y,0,1 }, float4{ LifeBarScale.x,LifeBarScale.y,0,1 }, CurHP / Data.Hp);
	float4 CurHpBarXPos = float4::LerpClamp(float4{ -LifeBarScale.hx(),LifeBarLocalPos.y,0,1 }, float4{ 0,LifeBarLocalPos.y,0,1 }, CurHP / Data.Hp);
	LifeBar->GetTransform()->SetWorldScale(CurHpBarXSize);
	LifeBar->GetTransform()->SetLocalPosition(CurHpBarXPos);
}

void BaseFighter::IdleAutoHeal(float _DeltaTime)
{
	if (CurHP >= Data.Hp)
	{
		CurHP = Data.Hp;
		Time = 0.f;
	}
	else
	{
		HealTime += _DeltaTime;
		if (HealTime >= 0.5f)
		{
			CurHP += (Data.Hp / 10);
			HealTime = 0.f;
		}
	}
}


