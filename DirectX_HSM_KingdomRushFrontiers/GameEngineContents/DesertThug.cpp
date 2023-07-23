#include "PrecompileHeader.h"
#include "DesertThug.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase\GameEngineRandom.h>

GameEngineSoundPlayer DesertThug::DeathSound = GameEngineSoundPlayer();

DesertThug::DesertThug()
{

}

DesertThug::~DesertThug()
{

}

void DesertThug::Start()
{
	BaseMonster::Start();
	Data.SetData(MonsterEnum::DesertThug);
	MonsterRenderer->CreateAnimation({.AnimationName = "Idle", .SpriteName = "DesertThug_Idle", .FrameInter = 0.06f, .Loop = false});
	MonsterRenderer->CreateAnimation({.AnimationName = "Move_Back", .SpriteName = "DesertThug_Move_Back", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Front", .SpriteName = "DesertThug_Move_Front", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Profile", .SpriteName = "DesertThug_Move_Profile", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "DesertThug_Attack", .FrameInter = 0.075f, .Loop = false});
	MonsterRenderer->CreateAnimation({.AnimationName = "Death", .SpriteName = "DesertThug_Death", .FrameInter = 0.06f, .Loop = false});
	MonsterRenderer->CreateAnimation({.AnimationName = "Death_Explosion", .SpriteName = "Small_Explosion", .FrameInter = 0.06f, .Loop = false});
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	MonsterCol->GetTransform()->SetLocalPosition(ColLocalPos);
	CurHP = Data.Hp;

	MonsterRenderer->SetAnimationStartEvent("Attack", 3, std::bind(&DesertThug::Attack, this));

	IdleStateInit();
	MoveStateInit();
	AttackStateInit();
	DeathStateInit();

	MonsterFSM.ChangeState("Move");
	DeathSoundPtr = &DeathSound;
	BaseMonster::PlayDeathSound = [this]()
	{
		BaseMonster::PlayHumanDeathSound();
	};

	MonsterRenderer->SetAnimationStartEvent("Death_Explosion", 0, [this]()
		{
			BaseMonster::PlayExplosionDeathSound();
		});

	MonsterRenderer->SetAnimationStartEvent("Death", 0, [this]()
		{
			BaseMonster::PlayDeathSound();
		});
}

void DesertThug::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}
