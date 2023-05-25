#include "PrecompileHeader.h"
#include "DesertThug.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

DesertThug::DesertThug()
{

}

DesertThug::~DesertThug()
{

}

void DesertThug::Start()
{
	BaseMonster::Start();
	MonsterRenderer->CreateAnimation({.AnimationName = "Idle", .SpriteName = "DesertThug_Idle", .FrameInter = 0.1f, .Loop = false});
	MonsterRenderer->CreateAnimation({.AnimationName = "Move_Back", .SpriteName = "DesertThug_Move_Back", .FrameInter = 0.1f, .Loop = true});
	MonsterRenderer->CreateAnimation({.AnimationName = "Move_Front", .SpriteName = "DesertThug_Move_Front", .FrameInter = 0.1f, .Loop = true });
	MonsterRenderer->CreateAnimation({.AnimationName = "Move_Profile", .SpriteName = "DesertThug_Move_Profile", .FrameInter = 0.1f, .Loop = true });
	MonsterRenderer->CreateAnimation({.AnimationName = "Attack", .SpriteName = "DesertThug_Attack", .FrameInter = 0.1f, .Loop = false});
	MonsterRenderer->CreateAnimation({.AnimationName = "Death", .SpriteName = "DesertThug_Death", .FrameInter = 0.08f, .Loop = false});
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	MonsterCol->GetTransform()->SetLocalPosition(ColLocalPos);
	Data.SetData(MonsterEnum::DesertThug);
	CurHP = Data.Hp;

	IdleStateInit();
	MoveStateInit();
	AttackStateInit();
	DeathStateInit();

	MonsterFSM.ChangeState("Move");
}

void DesertThug::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}

