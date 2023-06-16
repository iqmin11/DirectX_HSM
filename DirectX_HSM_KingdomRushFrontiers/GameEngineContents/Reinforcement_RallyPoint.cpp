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

std::shared_ptr<Reinforcement_RallyPoint> Reinforcement_RallyPoint::CreateRallyPoint(GameEngineLevel* _Level, const float4& _Pos, int _FighterCount)
{
	std::shared_ptr<Reinforcement_RallyPoint> LocalAc = nullptr;
	LocalAc = _Level->CreateActor<Reinforcement_RallyPoint>();
	LocalAc->GetTransform()->SetWorldPosition(_Pos);
	LocalAc->SetFighter(_FighterCount);
	return LocalAc;
}

void Reinforcement_RallyPoint::Start()
{
	RallyPoint::Start();
}

void Reinforcement_RallyPoint::Update(float _DeltaTime)
{
	RallyPoint::Update(_DeltaTime);

	LiveTime += _DeltaTime;
	if (LiveTime >= 20.f)
	{
		Death();
	}
}

void Reinforcement_RallyPoint::SetFighter(int _Count)
{
	Fighters.resize(3);
	FighterMaxCount = _Count;
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
		Fighters[i]->Data.SetData(FighterEnum::ReinforceLv0);
		Fighters[i]->CurHP = Fighters[i]->Data.Hp;
	}
}
