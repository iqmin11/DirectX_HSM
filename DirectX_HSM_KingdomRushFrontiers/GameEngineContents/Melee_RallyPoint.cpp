#include "PrecompileHeader.h"
#include "Melee_RallyPoint.h"

#include <GameEngineCore/GameEngineLevel.h>
#include "Melee_Fighter.h"


Melee_RallyPoint::Melee_RallyPoint()
{

}

Melee_RallyPoint::~Melee_RallyPoint()
{

}

std::shared_ptr<Melee_RallyPoint> Melee_RallyPoint::CreateRallyPoint(GameEngineLevel* _Level, const float4& _Pos, int _FighterCount)
{
	std::shared_ptr<Melee_RallyPoint> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Melee_RallyPoint>();
	LocalAc->GetTransform()->SetWorldPosition(_Pos);
	LocalAc->SetFighter(_FighterCount);
	return LocalAc;
}

void Melee_RallyPoint::ChangeFighters(int _TowerLevel)
{
	for (size_t i = 0; i < Fighters.size(); i++)
	{
		Fighters[i]->DynamicThis<Melee_Fighter>()->ChangeFighter(_TowerLevel);
	}
}

void Melee_RallyPoint::Start()
{
	RallyPoint::Start();
}

void Melee_RallyPoint::Update(float _DeltaTime)
{
	RallyPoint::Update(_DeltaTime);
}

void Melee_RallyPoint::SetFighter(int _Count)
{
	Fighters.resize(_Count);
	FighterMaxCount = _Count;
	for (size_t i = 0; i < Fighters.size(); i++)
	{
		Fighters[i] = GetLevel()->CreateActor<Melee_Fighter>();
		Fighters[i]->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
		Fighters[i]->SetParentRally(this);
		Fighters[i]->SetPrevPos(GetTransform()->GetWorldPosition());
		Fighters[i]->SetRallyTransform(RallyPosCheckComponents[i]->GetTransform());
		Fighters[i]->Data.SetData(FighterEnum::MeleeLv1);
		Fighters[i]->CurHP = Fighters[i]->Data.Hp;
	}
}
