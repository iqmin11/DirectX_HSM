#include "PrecompileHeader.h"
#include "Melee_Fighter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseMonster.h"


Melee_Fighter::Melee_Fighter()
{

}

Melee_Fighter::~Melee_Fighter()
{

}

void Melee_Fighter::ChangeFighter(int _TowerLevel)
{
	Data.SetData(_TowerLevel);
	CurHP = Data.Hp;
	std::string CurState = std::string();

	switch (State)
	{
	case FighterState::Idle:
		CurState = "_Idle";
		break;
	case FighterState::Move:
		CurState = "_Move";
		break;
	case FighterState::TraceMonster:
		CurState = "_Move";
		break;
	case FighterState::Attack:
		CurState = "_Attack";
		break;
	case FighterState::Return:
		CurState = "_Move";
		break;
	case FighterState::Death:
		CurState = "_Death";
		break;
	default:
		break;
	}
	FighterRenderer->ChangeAnimation(std::to_string(_TowerLevel) + CurState);
}

void Melee_Fighter::Start()
{
	BaseFighter::Start();
	BaseFighter::AttackTarget = std::bind(&Melee_Fighter::AttackTarget, this);

	FighterRenderer->CreateAnimation({ .AnimationName = "1_Idle", .SpriteName = "MeleeLv1_Fighter_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Move", .SpriteName = "MeleeLv1_Fighter_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Attack", .SpriteName = "MeleeLv1_Fighter_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Death", .SpriteName = "MeleeLv1_Fighter_Death", .Loop = false  });

	FighterRenderer->CreateAnimation({ .AnimationName = "2_Idle", .SpriteName = "MeleeLv2_Fighter_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Move", .SpriteName = "MeleeLv2_Fighter_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Attack", .SpriteName = "MeleeLv2_Fighter_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Death", .SpriteName = "MeleeLv2_Fighter_Death", .Loop = false });

	FighterRenderer->CreateAnimation({ .AnimationName = "3_Idle", .SpriteName = "MeleeLv3_Fighter_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Move", .SpriteName = "MeleeLv3_Fighter_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Attack", .SpriteName = "MeleeLv3_Fighter_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Death", .SpriteName = "MeleeLv3_Fighter_Death", .Loop = false });

	FighterRenderer->CreateAnimation({ .AnimationName = "4_Idle", .SpriteName = "MeleeLv4_Fighter_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Move", .SpriteName = "MeleeLv4_Fighter_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Attack", .SpriteName = "MeleeLv4_Fighter_Attack", .FrameInter = 0.05f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Death", .SpriteName = "MeleeLv4_Fighter_Death", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "4_Skill0", .SpriteName = "MeleeLv4_Fighter_Skill0", .FrameInter = 0.05f, .Loop = false });

	FighterRenderer->SetAnimationStartEvent("1_Attack", 2, std::bind(&Melee_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("2_Attack", 2, std::bind(&Melee_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("3_Attack", 2, std::bind(&Melee_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("4_Attack", 2, std::bind(&Melee_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("4_Skill0", 13, std::bind(&Melee_Fighter::SneakAttack, this));

	FighterRenderer->GetTransform()->SetWorldScale({128,128,1});

	IdleStateInit();
	MoveStateInit();
	TraceMonsterStateInit();
	AttackStateInit();
	ReturnStateInit();
	DeathStateInit();
}

void Melee_Fighter::Update(float _DeltaTime)
{
	BaseFighter::Update(_DeltaTime);
	FighterFSM.Update(_DeltaTime);
}

void Melee_Fighter::AttackTarget()
{
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->Hit = HitState::Melee;
}

void Melee_Fighter::SneakAttack()
{
	TargetMonster->CurHP -= CalSneakAttackDamage();
	TargetMonster->Hit = HitState::Melee;
}

int Melee_Fighter::CalDamage()
{
	return BaseFighter::CalDamage();
}

int Melee_Fighter::CalSneakAttackDamage()
{
	return GameEngineRandom::MainRandom.RandomInt(SneakAttack_min, SneakAttack_MAX);
}

