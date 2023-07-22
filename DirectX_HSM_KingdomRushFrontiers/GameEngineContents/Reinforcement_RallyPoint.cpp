#include "PrecompileHeader.h"
#include "Reinforcement_RallyPoint.h"

#include "PlayManager.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include "Reinforcement_Fighter.h"

std::list<std::weak_ptr<Reinforcement_RallyPoint>> Reinforcement_RallyPoint::LiveReinforcementRallyManager = std::list<std::weak_ptr<Reinforcement_RallyPoint>>();

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
	LiveReinforcementRallyManager.push_back(LocalAc);
	LocalAc->ReinforcementSound = GameEngineSound::Play("Reinforcements_Event" + std::to_string(GameEngineRandom::MainRandom.RandomInt(1, 4)) + ".ogg");
	LocalAc->ReinforcementSound.SetVolume(0.5f);
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
			LiveReinforcementRallyManager.pop_front(); // 로직상 문제는없지만 this를 찾아서 팝하는게 더 안전할것같음.
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
		Fighters[i]->SetParentRally(this);
		Fighters[i]->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
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
