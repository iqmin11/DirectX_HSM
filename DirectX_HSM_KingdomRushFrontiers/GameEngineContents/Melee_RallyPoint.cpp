#include "PrecompileHeader.h"
#include "Melee_RallyPoint.h"

#include <GameEngineCore/GameEngineLevel.h>
#include "Melee_Fighter.h"
#include "Melee_Tower.h"


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

	{
		if (Fighters[0] == nullptr && RespawnTimer0 == 0.f)
		{
			IsRespawnTimer0Update = true;
		}

		if (IsRespawnTimer0Update == true)
		{
			RespawnTimer0 += _DeltaTime;
		}

		if (RespawnTimer0 >= RespawnTime)
		{
			RespawnFighter(0);
			RespawnTimer0 = 0.f;
			IsRespawnTimer0Update = false;
		}
	}

	{
		if (Fighters[1] == nullptr && RespawnTimer1 == 0.f)
		{
			IsRespawnTimer1Update = true;
		}

		if (IsRespawnTimer1Update == true)
		{
			RespawnTimer1 += _DeltaTime;
		}

		if (RespawnTimer1 >= RespawnTime)
		{
			RespawnFighter(1);
			RespawnTimer1 = 0.f;
			IsRespawnTimer1Update = false;
		}
	}

	{
		if (Fighters[2] == nullptr && RespawnTimer2 == 0.f)
		{
			IsRespawnTimer2Update = true;
		}
		if (IsRespawnTimer2Update == true)
		{
			RespawnTimer2 += _DeltaTime;
		}

		if (RespawnTimer2 >= RespawnTime)
		{
			RespawnFighter(2);
			RespawnTimer2 = 0.f;
			IsRespawnTimer2Update = false;
		}
	}
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

void Melee_RallyPoint::RespawnFighter(int _index)
{
	Fighters[_index] = GetLevel()->CreateActor<Melee_Fighter>();
	Fighters[_index]->GetTransform()->SetWorldPosition(GetTransform()->GetParent()->GetWorldPosition());
	Fighters[_index]->SetParentRally(this);
	Fighters[_index]->SetPrevPos(GetTransform()->GetParent()->GetWorldPosition());
	Fighters[_index]->SetRallyTransform(RallyPosCheckComponents[_index]->GetTransform());
	Fighters[_index]->Data.SetData(DataPtr->Level);
	Fighters[_index]->CurHP = Fighters[_index]->Data.Hp;
}
