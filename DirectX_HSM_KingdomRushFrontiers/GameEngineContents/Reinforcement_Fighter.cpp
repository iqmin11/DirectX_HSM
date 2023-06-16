#include "PrecompileHeader.h"
#include "Reinforcement_Fighter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Reinforcement_Fighter::Reinforcement_Fighter()
{

}

Reinforcement_Fighter::~Reinforcement_Fighter()
{

}

void Reinforcement_Fighter::Start()
{
	BaseFighter::Start();
	BaseFighter::AttackTarget = std::bind(&Reinforcement_Fighter::AttackTarget, this);

	FighterRenderer->CreateAnimation({ .AnimationName = "0_Idle", .SpriteName = "MeleeLv1_Fighter_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Move", .SpriteName = "MeleeLv1_Fighter_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Attack", .SpriteName = "MeleeLv1_Fighter_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Death", .SpriteName = "MeleeLv1_Fighter_Death", .Loop = false });

	FighterRenderer->CreateAnimation({ .AnimationName = "1_Idle", .SpriteName = "MeleeLv2_Fighter_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Move", .SpriteName = "MeleeLv2_Fighter_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Attack", .SpriteName = "MeleeLv2_Fighter_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Death", .SpriteName = "MeleeLv2_Fighter_Death", .Loop = false });

	FighterRenderer->CreateAnimation({ .AnimationName = "2_Idle", .SpriteName = "MeleeLv3_Fighter_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Move", .SpriteName = "MeleeLv3_Fighter_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Attack", .SpriteName = "MeleeLv3_Fighter_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Death", .SpriteName = "MeleeLv3_Fighter_Death", .Loop = false });

	FighterRenderer->SetAnimationStartEvent("0_Attack", 2, std::bind(&Reinforcement_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("1_Attack", 2, std::bind(&Reinforcement_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("2_Attack", 2, std::bind(&Reinforcement_Fighter::AttackTarget, this));

	FighterRenderer->GetTransform()->SetWorldScale(FighterRendererScale);

	IdleStateInit();
	MoveStateInit();
	TraceMonsterStateInit();
	AttackStateInit();
	ReturnStateInit();
	DeathStateInit();

	FighterFSM.ChangeState("Idle");
}

void Reinforcement_Fighter::Update(float _DeltaTime)
{
	BaseFighter::Update(_DeltaTime);
}

void Reinforcement_Fighter::AttackTarget()
{
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->Hit = HitState::Melee;
}

int Reinforcement_Fighter::CalDamage()
{
	return BaseFighter::CalDamage();
}
