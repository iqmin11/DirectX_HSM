#include "PrecompileHeader.h"
#include "Reinforcement_RallyPoint.h"

#include <GameEngineCore/GameEngineLevel.h>
#include "Reinforcement_Fighter.h"

Reinforcement_RallyPoint::Reinforcement_RallyPoint()
{

}

Reinforcement_RallyPoint::~Reinforcement_RallyPoint()
{

}

std::shared_ptr<Reinforcement_RallyPoint> Reinforcement_RallyPoint::CreateRallyPoint(GameEngineLevel* _Level, const float4& _Pos, FighterEnum _Fighter)
{
	std::shared_ptr<Reinforcement_RallyPoint> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Reinforcement_RallyPoint>();
	LocalAc->GetTransform()->SetWorldPosition(_Pos);
	LocalAc->SetFighter(_Fighter);
	return LocalAc;
}

void Reinforcement_RallyPoint::Start()
{
	RallyPoint::Start();
}

void Reinforcement_RallyPoint::Update(float _DeltaTime)
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

void Reinforcement_RallyPoint::SetFighter(FighterEnum _Enum)
{
	Fighters.resize(3);
	for (size_t i = 0; i < Fighters.size(); i++)
	{
		if (i == 2)
		{
			Fighters[i] = nullptr;
			continue;
		}
		Fighters[i] = GetLevel()->CreateActor<Reinforcement_Fighter>();
		Fighters[i]->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
		Fighters[i]->SetParentRally(this);
		Fighters[i]->SetPrevPos(GetTransform()->GetWorldPosition());
		Fighters[i]->SetRallyTransform(RallyPosCheckComponents[i]->GetTransform());
		Fighters[i]->Data.SetData(_Enum);
		Fighters[i]->FighterFSM.ChangeState("Idle");
		Fighters[i]->CurHP = Fighters[i]->Data.Hp;
	}
}

bool Reinforcement_RallyPoint::IsAllFightersDeath()
{
	return Fighters[0] == nullptr && Fighters[1] == nullptr && Fighters[2] == nullptr;
}
