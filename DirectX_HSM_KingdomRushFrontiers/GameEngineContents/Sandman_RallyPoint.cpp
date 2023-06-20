#include "PrecompileHeader.h"
#include "Sandman_RallyPoint.h"

#include <GameEngineCore/GameEngineLevel.h>
#include "Sandman_Fighter.h"
#include "Hero_Alric.h"

Sandman_RallyPoint::Sandman_RallyPoint()
{

}

Sandman_RallyPoint::~Sandman_RallyPoint()
{

}

std::shared_ptr<Sandman_RallyPoint> Sandman_RallyPoint::CreateRallyPoint(Hero_Alric* _Hero, const float4& _Pos)
{
	std::shared_ptr<Sandman_RallyPoint> LocalAc = nullptr;
	LocalAc = _Hero->GetLevel()->CreateActor<Sandman_RallyPoint>();
	LocalAc->ParentHero = _Hero;
	LocalAc->GetTransform()->SetParent(_Hero->GetTransform(), false);
	LocalAc->GetTransform()->SetWorldPosition(_Pos);
	LocalAc->SetFighter();
	return LocalAc;
}

void Sandman_RallyPoint::Start()
{
	RallyPoint::Start();
}

void Sandman_RallyPoint::Update(float _DeltaTime)
{
	RallyPoint::Update(_DeltaTime);
	if (IsAllFightersDeath())
	{
		DeathTime += _DeltaTime;
		if (DeathTime >= 3.f)
		{
			Death();
		}
	}
}

void Sandman_RallyPoint::SetFighter()
{
	Fighters.resize(3);
	for (size_t i = 0; i < Fighters.size(); i++)
	{
		Fighters[i] = GetLevel()->CreateActor<Sandman_Fighter>();
		Fighters[i]->GetTransform()->SetWorldPosition(ParentHero->GetSandmanPivot()[i]->GetTransform()->GetWorldPosition());
		Fighters[i]->SetParentRally(this);
		Fighters[i]->SetPrevPos(ParentHero->GetSandmanPivot()[i]->GetTransform()->GetWorldPosition());
		Fighters[i]->SetRallyTransform(RallyPosCheckComponents[i]->GetTransform());
		Fighters[i]->Data.SetData(FighterEnum::Creature_Sandman);
		Fighters[i]->FighterFSM.ChangeState("Born");
		Fighters[i]->CurHP = Fighters[i]->Data.Hp;
	}
}

bool Sandman_RallyPoint::IsAllFightersDeath()
{
	return Fighters[0] == nullptr && Fighters[1] == nullptr && Fighters[2] == nullptr;
}
