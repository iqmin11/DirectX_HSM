#include "PrecompileHeader.h"
#include "GiantWaspQueen.h"
#include <GameEngineBase\GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "GiantWasp.h"
#include <GameEngineCore\GameEngineLevel.h>

GameEngineSoundPlayer GiantWaspQueen::DeathSound = GameEngineSoundPlayer();
GameEngineSoundPlayer GiantWaspQueen::MoveSound = GameEngineSoundPlayer();

GiantWaspQueen::GiantWaspQueen()
{

}

GiantWaspQueen::~GiantWaspQueen()
{

}

void GiantWaspQueen::Start()
{
	BaseMonster::Start();
	Data.SetData(MonsterEnum::GiantWaspQueen);
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Back", .SpriteName = "GiantWaspQueen_Move_Back", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Front", .SpriteName = "GiantWaspQueen_Move_Front", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Profile", .SpriteName = "GiantWaspQueen_Move_Profile", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "GiantWaspQueen_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death_Explosion", .SpriteName = "GiantWaspQueen_Death", .FrameInter = 0.06f, .Loop = false });
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

	SetHPBarPos(100);

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

void GiantWaspQueen::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}

void GiantWaspQueen::PlayMoveSound()
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

void GiantWaspQueen::SummonWasp()
{
	std::weak_ptr<GiantWasp> Result(GetLevel()->CreateActor<GiantWasp>());
	Result.lock()->SetWalk(Walk);
	Result.lock()->GetTransform()->SetWorldPosition(Walk.ActorPos);
}