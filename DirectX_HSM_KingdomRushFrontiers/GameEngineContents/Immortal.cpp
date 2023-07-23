#include "PrecompileHeader.h"
#include "Immortal.h"
#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Fallen.h"
#include <GameEngineBase\GameEngineRandom.h>

GameEngineSoundPlayer Immortal::DeathSound = GameEngineSoundPlayer();

Immortal::Immortal()
{

}

Immortal::~Immortal()
{

}

void Immortal::Start()
{
	BaseMonster::Start();
	Data.SetData(MonsterEnum::Immortal);
	MonsterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Immortal_Idle", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Back", .SpriteName = "Immortal_Move_Back", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Front", .SpriteName = "Immortal_Move_Front", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Profile", .SpriteName = "Immortal_Move_Profile", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Immortal_Attack", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Immortal_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death_Explosion", .SpriteName = "Immortal_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	MonsterCol->GetTransform()->SetLocalPosition(ColLocalPos);
	CurHP = Data.Hp;

	MonsterRenderer->SetAnimationStartEvent("Attack", 3, std::bind(&Immortal::Attack, this));

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

void Immortal::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}

void Immortal::SummonFallen()
{
	std::weak_ptr<Fallen> Result(GetLevel()->CreateActor<Fallen>());
	Result.lock()->SetWalk(Walk);
	Result.lock()->GetTransform()->SetWorldPosition(Walk.ActorPos);
}
