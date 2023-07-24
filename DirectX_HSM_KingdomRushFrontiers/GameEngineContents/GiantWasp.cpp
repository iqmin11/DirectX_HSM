#include "PrecompileHeader.h"
#include "GiantWasp.h"
#include <GameEngineBase\GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

GameEngineSoundPlayer GiantWasp::DeathSound = GameEngineSoundPlayer();
GameEngineSoundPlayer GiantWasp::MoveSound = GameEngineSoundPlayer();

GiantWasp::GiantWasp()
{

}

GiantWasp::~GiantWasp()
{

}

void GiantWasp::Start()
{
	BaseMonster::Start();
	Data.SetData(MonsterEnum::GiantWasp);
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Back", .SpriteName = "GiantWasp_Move_Back", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Front", .SpriteName = "GiantWasp_Move_Front", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Profile", .SpriteName = "GiantWasp_Move_Profile", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "GiantWasp_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death_Explosion", .SpriteName = "GiantWasp_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterRenderer->GetTransform()->SetLocalPosition(ColLocalPos);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	MonsterCol->GetTransform()->SetLocalPosition(ColLocalPos);
	CurHP = Data.Hp;

	MoveStateInit();
	DeathStateInit();

	MonsterFSM.ChangeState("Move");

	Shadow = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	Shadow->GetTransform()->SetWorldScale(ShdowScale);
	Shadow->SetTexture("FlyingEnemiesShadow.png");

	SetHPBarPos(70);

	DeathSoundPtr = &DeathSound;
	BaseMonster::PlayDeathSound = [this]()
	{
		BaseMonster::PlayExplosionDeathSound();
	};

	MonsterRenderer->SetAnimationStartEvent("Death_Explosion", 0, [this]()
		{
			BaseMonster::PlayDeathSound();
		});

	MonsterRenderer->SetAnimationStartEvent("Death", 0, [this]()
		{
			BaseMonster::PlayDeathSound();
		});
	
	MonsterRenderer->SetAnimationStartEvent("Move_Back", 0, [this]()
		{
			PlayMoveSound();
		});

	MonsterRenderer->SetAnimationStartEvent("Move_Front", 0, [this]()
		{
			PlayMoveSound();
		});

	MonsterRenderer->SetAnimationStartEvent("Move_Profile", 0, [this]()
		{
			PlayMoveSound();
		});

}

void GiantWasp::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}

void GiantWasp::PlayMoveSound()
{
	if (MoveSound.IsValid())
	{
		bool Value = false;
		MoveSound.isPlaying(&Value);
		if (Value)
		{
			return;
		}
	}
	MoveSound = GameEngineSound::Play("wasp_" + std::to_string(GameEngineRandom::MainRandom.RandomInt(1, 3)) + ".ogg");
	MoveSound.SetVolume(0.2f);
}

