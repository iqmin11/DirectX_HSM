#include "PrecompileHeader.h"
#include "PlayManager.h"

#include "Melee_Tower.h"
#include <GameEngineCore\GameEngineLevel.h>
#include "PlayStageLevel.h"

PlayManager* PlayManager::MainPlayer = nullptr;
Melee_Tower* PlayManager::SelectedMeleeTower = nullptr;

PlayManager::PlayManager()
{
	if (MainPlayer != nullptr)
	{
		return;
	}
	MainPlayer = this;
}

PlayManager::~PlayManager()
{
}

const std::weak_ptr<class Hero_RallyPoint> PlayManager::GetHero() const
{
	return std::weak_ptr(dynamic_cast<PlayStageLevel*>(GetLevel())->GetHero());
}

void PlayManager::Start()
{
	Data.ReinforceLevel = 3;

	IdleStateInit();
	RainOfFireStateInit();
	CallReinforcementStateInit();
	HeroStateInit();
	TowerStateInit();
	UnitPosStateInit();
	PlayerFSM.ChangeState("Idle");
}

void PlayManager::Update(float _DeltaTime)
{
	PlayerFSM.Update(_DeltaTime);
	CalCoolTime_RainOfFire(_DeltaTime);
	CalCoolTime_CallReinforcement(_DeltaTime);
}

void PlayManager::CalCoolTime_RainOfFire(float _DeltaTime)
{
	if (!Available_RainOfFire)
	{
		RainOfFire_Cooltime += _DeltaTime;
		if (RainOfFire_Cooltime >= RainOfFire_MaxCool)
		{
			Available_RainOfFire = true;
		}
	}
}

void PlayManager::CalCoolTime_CallReinforcement(float _DeltaTime)
{
	if (!Available_CallReinforcement)
	{
		CallReinforcement_Cooltime += _DeltaTime;
		if (CallReinforcement_Cooltime >= CallReinforcement_MaxCool)
		{
			Available_CallReinforcement = true;
		}
	}
}



