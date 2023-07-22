#include "PrecompileHeader.h"
#include "DesertThug.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseFighter.h"

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

	DeathSoundNames.resize(4);
	DeathSoundNames[0] = "Sound_HumanDead1.ogg";
	DeathSoundNames[1] = "Sound_HumanDead2.ogg";
	DeathSoundNames[2] = "Sound_HumanDead3.ogg";
	DeathSoundNames[3] = "Sound_HumanDead4.ogg";

	BaseMonster::PlayDeathSound = std::bind(&DesertThug::PlayDeathSound, this);
}

void DesertThug::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}

void DesertThug::PlayDeathSound()
{
	if (DeathSound.IsValid())
	{
		bool Value = false;
		DeathSound.isPlaying(&Value);
		if (Value)
		{
			return;
		}
	}
	DeathSound = GameEngineSound::Play(DeathSoundNames[GameEngineRandom::MainRandom.RandomInt(0,3)]);
	DeathSound.SetVolume(0.2f);
}
