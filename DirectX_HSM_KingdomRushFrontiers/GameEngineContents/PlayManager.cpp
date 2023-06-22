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
}


