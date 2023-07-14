#include "PrecompileHeader.h"
#include "GiantWaspQueen.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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

	SetHPBarPos(100);
}

void GiantWaspQueen::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}
