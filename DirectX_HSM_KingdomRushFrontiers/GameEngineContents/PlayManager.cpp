#include "PrecompileHeader.h"
#include "PlayManager.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "Melee_Tower.h"
#include "PlayStageLevel.h"
#include "Hero_RallyPoint.h"
#include "Hero_Alric.h"

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

void PlayManager::InitPlayManager()
{
	Life = 20;

	RainOfFire_Cooltime = 80.f;
	RainOfFire_MaxCool = 80.f;
	Available_RainOfFire = false;

	CallReinforcement_Cooltime = 10.f;
	CallReinforcement_MaxCool = 10.f;
	Available_CallReinforcement = false;

	State = PlayerState::Idle;
	PlayerFSM.ChangeState("Idle");
}

const std::weak_ptr<class Hero_RallyPoint> PlayManager::GetHeroRally() const
{
	return std::weak_ptr(dynamic_cast<PlayStageLevel*>(GetLevel())->GetHero());
}

FighterState PlayManager::GetHeroState() const
{
	return GetHeroRally().lock()->GetHero().lock()->GetState();
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

void PlayManager::PlayerSound(const std::string_view& _FileName, float _Volum)
{
	PlayManagerSound = GameEngineSound::Play(_FileName);
	PlayManagerSound.SetVolume(_Volum);
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



