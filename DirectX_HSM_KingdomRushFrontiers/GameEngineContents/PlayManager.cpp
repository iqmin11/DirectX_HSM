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
	AcHero = dynamic_cast<PlayStageLevel*>(GetLevel())->GetHero();
}

void PlayManager::Update(float _DeltaTime)
{
	PlayerFSM.Update(_DeltaTime);
}


