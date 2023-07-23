#include "PrecompileHeader.h"
#include "SandHound.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

GameEngineSoundPlayer SandHound::DeathSound = GameEngineSoundPlayer();

SandHound::SandHound()
{

}

SandHound::~SandHound()
{

}

void SandHound::Start()
{
	BaseMonster::Start();
	Data.SetData(MonsterEnum::SandHound);
	MonsterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "SandHound_Idle", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Back", .SpriteName = "SandHound_Move_Back", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Front", .SpriteName = "SandHound_Move_Front", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Profile", .SpriteName = "SandHound_Move_Profile", .FrameInter = 0.03f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "SandHound_Attack", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "SandHound_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death_Explosion", .SpriteName = "SandHound_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	MonsterCol->GetTransform()->SetLocalPosition(ColLocalPos);
	CurHP = Data.Hp;

	MonsterRenderer->SetAnimationStartEvent("Attack", 3, std::bind(&SandHound::Attack, this));

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

void SandHound::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}
