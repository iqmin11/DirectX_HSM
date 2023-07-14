#include "PrecompileHeader.h"
#include "GiantWasp.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death_Explosion", .SpriteName = "Small_Explosion", .FrameInter = 0.06f, .Loop = false });
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
}

void GiantWasp::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}


