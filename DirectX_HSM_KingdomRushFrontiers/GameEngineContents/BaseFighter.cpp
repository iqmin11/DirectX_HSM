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
	DeathStateInit();

	FighterFSM.ChangeState("Idle");
}

void BaseFighter::Update(float _DeltaTime)
{
	if (ParentRally == nullptr)
	{
		MsgAssert("Fighter의 부모 랠리포인트가 설정되지 않았습니다.")
	}
	FighterFSM.Update(_DeltaTime);
}


void BaseFighter::AttackTarget()
{
	TargetMonster->CurHP -= 10;
}

void BaseFighter::MoveToTarget(float _DeltaTime)
{
	Time += _DeltaTime;
	float4 TargetPos = TargetMonster->GetTransform()->GetWorldPosition();
	Ratio = Time * (Speed / (TargetPos - PrevPos).Size());
	ActorPos = float4::LerpClamp(PrevPos, TargetPos, Ratio);
	GetTransform()->SetWorldPosition(ActorPos);
	if (FighterCol->GetTransform()->Collision({._OtherTrans = TargetMonster->GetMonsterCol()->GetTransform(), .ThisType = ColType::AABBBOX2D, .OtherType = ColType::AABBBOX2D}))
	{
		State = FighterState::Attack;
		Ratio = 0.f;
		Time = 0.f;
	}

	if (ActorPos.x - TargetPos.x > 0)
	{
		FighterRenderer->GetTransform()->SetLocalNegativeScaleX();
	}
	else if (ActorPos.x - TargetPos.x < 0)
	{
		FighterRenderer->GetTransform()->SetLocalPositiveScaleX();
	}
}


