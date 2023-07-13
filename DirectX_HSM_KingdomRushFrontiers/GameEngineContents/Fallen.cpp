#include "PrecompileHeader.h"
#include "Fallen.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore\GameEngineLevel.h>
#include "Immortal.h"

Fallen::Fallen()
{

}

Fallen::~Fallen()
{

}

void Fallen::Start()
{
	BaseMonster::Start();
	Data.SetData(MonsterEnum::Fallen);
	MonsterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Fallen_Idle", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Back", .SpriteName = "Fallen_Move_Back", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Front", .SpriteName = "Fallen_Move_Front", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Profile", .SpriteName = "Fallen_Move_Profile", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Fallen_Attack", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Fallen_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death_Explosion", .SpriteName = "Small_Explosion", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	MonsterCol->GetTransform()->SetLocalPosition(ColLocalPos);
	CurHP = Data.Hp;

	MonsterRenderer->SetAnimationStartEvent("Attack", 3, std::bind(&Fallen::Attack, this));

	IdleStateInit();
	MoveStateInit();
	AttackStateInit();
	DeathStateInit();

	MonsterFSM.ChangeState("Move");
}

void Fallen::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}
