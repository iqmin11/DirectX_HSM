#include "PrecompileHeader.h"
#include "DuneTerror.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

DuneTerror::DuneTerror()
{

}

DuneTerror::~DuneTerror()
{

}

void DuneTerror::Start()
{
	BaseMonster::Start();
	Data.SetData(MonsterEnum::DuneTerror);
	MonsterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "DuneTerror_Idle", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Back", .SpriteName = "DuneTerror_Move_Back", .FrameInter = 0.04f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Front", .SpriteName = "DuneTerror_Move_Front", .FrameInter = 0.04f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Profile", .SpriteName = "DuneTerror_Move_Profile", .FrameInter = 0.04f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "DuneTerror_Attack", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "DuneTerror_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death_Explosion", .SpriteName = "Small_Explosion", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "ComeUp", .SpriteName = "DuneTerror_Come_Up", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "GoDown", .SpriteName = "DuneTerror_Go_Down", .FrameInter = 0.06f, .Loop = false });
	
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	MonsterCol->GetTransform()->SetLocalPosition(ColLocalPos);
	CurHP = Data.Hp;

	MonsterRenderer->SetAnimationStartEvent("Attack", 3, std::bind(&DuneTerror::Attack, this));
	MonsterRenderer->SetAnimationStartEvent("GoDown", 7, [this]()
		{
			MonsterFSM.ChangeState("Move");
		});

	IdleStateInit();
	MoveStateInit();
	AttackStateInit();
	DeathStateInit();
	ComeUpStateInit();
	GoDownStateInit();

	MonsterFSM.ChangeState("Move");
}

void DuneTerror::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}


