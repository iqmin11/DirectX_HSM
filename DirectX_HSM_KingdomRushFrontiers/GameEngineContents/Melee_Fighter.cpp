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
	FighterRenderer->CreateAnimation({ .AnimationName = "1_Death", .SpriteName = "MeleeLv1_Fighter_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "2_Idle", .SpriteName = "MeleeLv2_Fighter_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Move", .SpriteName = "MeleeLv2_Fighter_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Attack", .SpriteName = "MeleeLv2_Fighter_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "2_Death", .SpriteName = "MeleeLv2_Fighter_Death", .Loop = true });

	FighterRenderer->CreateAnimation({ .AnimationName = "3_Idle", .SpriteName = "MeleeLv3_Fighter_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Move", .SpriteName = "MeleeLv3_Fighter_Move", .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Attack", .SpriteName = "MeleeLv3_Fighter_Attack", .FrameInter = 0.15f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "3_Death", .SpriteName = "MeleeLv3_Fighter_Death", .Loop = true });

	//FighterRenderer->CreateAnimation({ .AnimationName = "4_Idle", .SpriteName = "MeleeLv4_Fighter_Idle", .Loop = false });
	//FighterRenderer->CreateAnimation({ .AnimationName = "4_Move", .SpriteName = "MeleeLv4_Fighter_Move", .Loop = true });
	//FighterRenderer->CreateAnimation({ .AnimationName = "4_Attack", .SpriteName = "MeleeLv4_Fighter_Attack", .FrameInter = 0.15f, .Loop = false });
	//FighterRenderer->CreateAnimation({ .AnimationName = "4_Death", .SpriteName = "MeleeLv4_Fighter_Death", .Loop = true });

	FighterRenderer->SetAnimationStartEvent("1_Attack", 2, std::bind(&Melee_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("2_Attack", 2, std::bind(&Melee_Fighter::AttackTarget, this));
	FighterRenderer->SetAnimationStartEvent("3_Attack", 2, std::bind(&Melee_Fighter::AttackTarget, this));
	//FighterRenderer->SetAnimationStartEvent("4_Attack", 2, std::bind(&BaseFighter::AttackTarget, this));

	FighterRenderer->GetTransform()->SetWorldScale(FighterRendererScale);

	IdleStateInit();
	MoveStateInit();
	TraceMonsterStateInit();
	AttackStateInit();
	ReturnStateInit();
	DeathStateInit();

	FighterFSM.ChangeState("Idle");
}

void Melee_Fighter::Update(float _DeltaTime)
{
	BaseFighter::Update(_DeltaTime);
}

void Melee_Fighter::AttackTarget()
{
	TargetMonster->CurHP -= CalDamage();
}

int Melee_Fighter::CalDamage()
{
	return BaseFighter::CalDamage();
}
