#include "PrecompileHeader.h"
#include "Sandman_Fighter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Sandman_Fighter::Sandman_Fighter()
{

}

Sandman_Fighter::~Sandman_Fighter()
{

}

void Sandman_Fighter::Start()
{
	BaseFighter::Start();
	BaseFighter::AttackTarget = std::bind(&Sandman_Fighter::AttackTarget, this);

	FighterRenderer->CreateAnimation({ .AnimationName = "Born", .SpriteName = "Sandman_Born", .FrameInter = 0.075f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Sandman_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Move_Start", .SpriteName = "Sandman_MoveStart", .FrameInter = 0.075f, .Loop = false});
	FighterRenderer->CreateAnimation({ .AnimationName = "Move", .SpriteName = "Sandman_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "Move_End", .SpriteName = "Sandman_MoveEnd", .FrameInter = 0.075f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Move_Death", .SpriteName = "Sandman_MoveDeath", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Sandman_Attack", .FrameInter = 0.075f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Sandman_Death", .Loop = false });

	FighterRenderer->GetTransform()->SetWorldScale(RanderScale);
	FighterRenderer->SetAnimationStartEvent("Attack", 3, BaseFighter::AttackTarget);

	BornStateInit();
	IdleStateInit();
	MoveStartStateInit();
	MoveStateInit();
	MoveEndStateInit();
	StartTraceMonsterStateInit();
	TraceMonsterStateInit();
	EndTraceMonsterStateInit();
	AttackStateInit();
	MoveDeathStateInit();
	DeathStateInit();
}

void Sandman_Fighter::Update(float _DeltaTime)
{
	BaseFighter::Update(_DeltaTime);
	FighterFSM.Update(_DeltaTime);

	if (8.f <= LiveTime && State != FighterState::Death)
	{
		if (State == FighterState::Move)
		{
			State = FighterState::Death;
			FighterFSM.ChangeState("MoveDeath");
		}
		else
		{
			State = FighterState::Death;
			FighterFSM.ChangeState("Death");
		}
	}
}

void Sandman_Fighter::AttackTarget()
{
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->Hit = HitState::Melee;
}

int Sandman_Fighter::CalDamage()
{
	return BaseFighter::CalDamage();
}