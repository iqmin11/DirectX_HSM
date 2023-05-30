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

}

void BaseFighter::ResetRatio()
{
	Time = 0.f;
	Ratio = 0.f;
}

void BaseFighter::Start()
{
	FighterRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	FighterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "ReinforceA_0_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Move", .SpriteName = "ReinforceA_0_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "ReinforceA_0_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "ReinforceA_0_Death", .Loop = true });
	FighterRenderer->SetAnimationStartEvent("Attack", 2, std::bind(&BaseFighter::AttackTarget, this));
	FighterRenderer->GetTransform()->SetWorldScale(FighterRendererScale);

	FighterCol = CreateComponent<GameEngineCollision>(ColOrder::Fighter);
	FighterCol->GetTransform()->SetWorldScale(ColScale);
	FighterCol->GetTransform()->SetLocalPosition(ColLocalPos);

	IdleStateInit();
	MoveStateInit();
	TraceMonsterStateInit();
	AttackStateInit();
	ReturnStateInit();
	DeathStateInit();

	FighterFSM.ChangeState("Idle");
}

void BaseFighter::Update(float _DeltaTime)
{
	if (ParentRally == nullptr)
	{
		MsgAssert("Fighter의 부모 랠리포인트가 설정되지 않았습니다.")
	}

	if (ParentRally->IsDeath())
	{
		Death();
	}

	FighterFSM.Update(_DeltaTime);
}



void BaseFighter::MoveToRally(float _DeltaTime)
{
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

void BaseFighter::AttackTarget()
{
	TargetMonster->CurHP -= 5;
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
	if (FighterCol->GetTransform()->Collision({._OtherTrans = TargetMonster->GetMonsterCol()->GetTransform(), .ThisType = ColType::AABBBOX2D, .OtherType = ColType::AABBBOX2D}))
	{
		State = FighterState::Attack;
		SavePos = GetTransform()->GetWorldPosition();
	}
}


