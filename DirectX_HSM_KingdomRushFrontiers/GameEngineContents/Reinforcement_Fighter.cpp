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

	int RandomInt = GameEngineRandom::MainRandom.RandomInt(0,2);
	switch (RandomInt)
	{
	case 0:
		SetAnimation_A();
		break;
	case 1:
		SetAnimation_B();
		break;
	case 2:
		SetAnimation_C();
		break;
	default:
		break;
	}

	FighterRenderer->SetAnimationStartEvent("0_Attack", 2, std::bind(&Reinforcement_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("1_Attack", 2, std::bind(&Reinforcement_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("2_Attack", 2, std::bind(&Reinforcement_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("3_Attack", 2, std::bind(&Reinforcement_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("4_Attack", 2, std::bind(&Reinforcement_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("5_Attack", 2, std::bind(&Reinforcement_Fighter::AttackTarget, this));

	FighterRenderer->GetTransform()->SetWorldScale(ReinforcementRenderScale);

	IdleStateInit();
	MoveStateInit();
	TraceMonsterStateInit();
	AttackStateInit();
	ReturnStateInit();
	DeathStateInit();
}

void Reinforcement_Fighter::Update(float _DeltaTime)
{
	BaseFighter::Update(_DeltaTime);
	FighterFSM.Update(_DeltaTime);

	LiveTime += _DeltaTime;
	if (20.f <= LiveTime && State != FighterState::Death)
	{
		State = FighterState::Death;
		FighterFSM.ChangeState("Death");
	}
}

void Reinforcement_Fighter::AttackTarget()
{
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->Hit = HitState::Melee;
	PlayAttackSound();
}

int Reinforcement_Fighter::CalDamage()
{
	return BaseFighter::CalDamage();
}

void Reinforcement_Fighter::SetAnimation_A()
{
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Idle", .SpriteName = "ReinforceA_0_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Move", .SpriteName = "ReinforceA_0_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Attack", .SpriteName = "ReinforceA_0_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Death", .SpriteName = "ReinforceA_0_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "1_Idle", .SpriteName = "ReinforceA_1_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Move", .SpriteName = "ReinforceA_1_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Attack", .SpriteName = "ReinforceA_1_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Death", .SpriteName = "ReinforceA_1_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "2_Idle", .SpriteName = "ReinforceA_2_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Move", .SpriteName = "ReinforceA_2_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Attack", .SpriteName = "ReinforceA_2_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Death", .SpriteName = "ReinforceA_2_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "3_Idle", .SpriteName = "ReinforceA_3_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Move", .SpriteName = "ReinforceA_3_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Attack", .SpriteName = "ReinforceA_3_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Death", .SpriteName = "ReinforceA_3_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "4_Idle", .SpriteName = "ReinforceA_4_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Move", .SpriteName = "ReinforceA_4_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Attack", .SpriteName = "ReinforceA_4_Attack", .FrameInter = 0.05f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Death", .SpriteName = "ReinforceA_4_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "5_Idle", .SpriteName = "ReinforceA_4_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "5_Move", .SpriteName = "ReinforceA_4_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "5_Attack", .SpriteName = "ReinforceA_4_Attack", .FrameInter = 0.05f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "5_Death", .SpriteName = "ReinforceA_4_Death", .Loop = true });
}

void Reinforcement_Fighter::SetAnimation_B()
{
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Idle", .SpriteName = "ReinforceB_0_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Move", .SpriteName = "ReinforceB_0_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Attack", .SpriteName = "ReinforceB_0_Attack", .FrameInter = 0.12f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Death", .SpriteName = "ReinforceB_0_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "1_Idle", .SpriteName = "ReinforceB_1_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Move", .SpriteName = "ReinforceB_1_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Attack", .SpriteName = "ReinforceB_1_Attack", .FrameInter = 0.12f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Death", .SpriteName = "ReinforceB_1_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "2_Idle", .SpriteName = "ReinforceB_2_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Move", .SpriteName = "ReinforceB_2_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Attack", .SpriteName = "ReinforceB_2_Attack", .FrameInter = 0.12f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Death", .SpriteName = "ReinforceB_2_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "3_Idle", .SpriteName = "ReinforceB_3_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Move", .SpriteName = "ReinforceB_3_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Attack", .SpriteName = "ReinforceB_3_Attack", .FrameInter = 0.12f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Death", .SpriteName = "ReinforceB_3_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "4_Idle", .SpriteName = "ReinforceB_4_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Move", .SpriteName = "ReinforceB_4_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Attack", .SpriteName = "ReinforceB_4_Attack", .FrameInter = 0.075f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Death", .SpriteName = "ReinforceB_4_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "5_Idle", .SpriteName = "ReinforceB_4_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "5_Move", .SpriteName = "ReinforceB_4_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "5_Attack", .SpriteName = "ReinforceB_4_Attack", .FrameInter = 0.075f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "5_Death", .SpriteName = "ReinforceB_4_Death", .Loop = true });
}

void Reinforcement_Fighter::SetAnimation_C()
{
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Idle", .SpriteName = "ReinforceC_0_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Move", .SpriteName = "ReinforceC_0_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Attack", .SpriteName = "ReinforceC_0_Attack", .FrameInter = 0.075f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "0_Death", .SpriteName = "ReinforceC_0_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "1_Idle", .SpriteName = "ReinforceC_1_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Move", .SpriteName = "ReinforceC_1_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Attack", .SpriteName = "ReinforceC_1_Attack", .FrameInter = 0.075f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Death", .SpriteName = "ReinforceC_1_Death", .Loop = true });


	FighterRenderer->CreateAnimation({ .AnimationName = "2_Idle", .SpriteName = "ReinforceC_2_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Move", .SpriteName = "ReinforceC_2_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Attack", .SpriteName = "ReinforceC_2_Attack", .FrameInter = 0.075f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Death", .SpriteName = "ReinforceC_2_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "3_Idle", .SpriteName = "ReinforceC_3_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Move", .SpriteName = "ReinforceC_3_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Attack", .SpriteName = "ReinforceC_3_Attack", .FrameInter = 0.075f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Death", .SpriteName = "ReinforceC_3_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "4_Idle", .SpriteName = "ReinforceC_4_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Move", .SpriteName = "ReinforceC_4_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Attack", .SpriteName = "ReinforceC_4_Attack", .FrameInter = 0.05f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Death", .SpriteName = "ReinforceC_4_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "5_Idle", .SpriteName = "ReinforceC_4_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "5_Move", .SpriteName = "ReinforceC_4_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "5_Attack", .SpriteName = "ReinforceC_4_Attack", .FrameInter = 0.05f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "5_Death", .SpriteName = "ReinforceC_4_Death", .Loop = true });
}
