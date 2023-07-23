#include "PrecompileHeader.h"
#include "WarHound.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

GameEngineSoundPlayer WarHound::DeathSound = GameEngineSoundPlayer();

WarHound::WarHound()
{

}

WarHound::~WarHound()
{

}

void WarHound::Start()
{
	BaseMonster::Start();
	Data.SetData(MonsterEnum::WarHound);
	MonsterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "WarHound_Idle", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Back", .SpriteName = "WarHound_Move_Back", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Front", .SpriteName = "WarHound_Move_Front", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Profile", .SpriteName = "WarHound_Move_Profile", .FrameInter = 0.03f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "WarHound_Attack", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "WarHound_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death_Explosion", .SpriteName = "WarHound_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	MonsterCol->GetTransform()->SetLocalPosition(ColLocalPos);
	CurHP = Data.Hp;

	MonsterRenderer->SetAnimationStartEvent("Attack", 3, std::bind(&WarHound::Attack, this));

	IdleStateInit();
	MoveStateInit();
	AttackStateInit();
	DeathStateInit();

	MonsterFSM.ChangeState("Move");

	DeathSoundPtr = &DeathSound;
	BaseMonster::PlayDeathSound = [this]()
	{
		BaseMonster::PlayPuffDeathSound();
	};

	MonsterRenderer->SetAnimationStartEvent("Death_Explosion", 0, [this]()
		{
			BaseMonster::PlayDeathSound();
		});

	MonsterRenderer->SetAnimationStartEvent("Death", 0, [this]()
		{
			BaseMonster::PlayDeathSound();
		});
}

void WarHound::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}
