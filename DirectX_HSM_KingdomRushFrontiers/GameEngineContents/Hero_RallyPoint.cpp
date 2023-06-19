#include "PrecompileHeader.h"
#include "Hero_RallyPoint.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineCollision.h>
#include "Hero_Alric.h"

Hero_RallyPoint::Hero_RallyPoint()
{

}

Hero_RallyPoint::~Hero_RallyPoint()
{

}

std::shared_ptr<Hero_RallyPoint> Hero_RallyPoint::CreateRallyPoint(GameEngineLevel* _Level, const float4& _Pos)
{
	std::shared_ptr<Hero_RallyPoint> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Hero_RallyPoint>();
	LocalAc->GetTransform()->SetWorldPosition(_Pos);
	LocalAc->SetHero();
	return LocalAc;
}

void Hero_RallyPoint::Start()
{
	RangeCol = CreateComponent<GameEngineCollision>(ColOrder::Fighter);
	RangeCol->GetTransform()->SetWorldScale({ Range * 2.f,Range * 2.f,0.f });
	RallyPosCheckComponents.push_back(CreateComponent<GameEngineComponent>());
}

void Hero_RallyPoint::Update(float _DeltaTime)
{
	if (IsThereTarget())
	{
		FindTarget();
	}
}

void Hero_RallyPoint::SetHero()
{
	Fighters.resize(3);
	Fighters[0] = GetLevel()->CreateActor<Hero_Alric>();
	Fighters[0]->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	Fighters[0]->SetParentRally(this);
	Fighters[0]->SetPrevPos(GetTransform()->GetWorldPosition());
	Fighters[0]->SetRallyTransform(RallyPosCheckComponents[0]->GetTransform());
	Fighters[0]->Data.SetData(FighterEnum::Hero_Alric);
	Fighters[0]->FighterFSM.ChangeState("Idle");
	Fighters[0]->CurHP = Fighters[0]->Data.Hp;
	Fighters[1] = nullptr;
	Fighters[2] = nullptr;
}
