#include "PrecompileHeader.h"
#include "PlayManager.h"

#include <GameEnginePlatform\GameEngineInput.h>
#include "MousePointer.h"

void PlayManager::IdleStateInit()
{
	PlayerFSM.CreateState({
	.Name = "Idle",
	.Start = [this]()
	{

	},
	.Update = [this](float _DeltaTime)
	{
		if (State == PlayerState::RainOfFire)
		{
			PlayerFSM.ChangeState("RainOfFire");
		}
		else if (State == PlayerState::CallReinforcement)
		{
			PlayerFSM.ChangeState("CallReinforcement");
		}
		else if (State == PlayerState::Hero)
		{
			PlayerFSM.ChangeState("Hero");
		}
		else if (State == PlayerState::UnitPos)
		{
			PlayerFSM.ChangeState("UnitPos");
		}
	},
	.End = [this]()
	{
	
	}
	});
}

void PlayManager::RainOfFireStateInit()
{
	PlayerFSM.CreateState({
	.Name = "RainOfFire",
	.Start = [this]()
	{

	},
	.Update = [this](float _DeltaTime)
	{
		if (State == PlayerState::Idle)
		{
			PlayerFSM.ChangeState("Idle");
		}
		else if (State == PlayerState::CallReinforcement)
		{
			PlayerFSM.ChangeState("CallReinforcement");
		}
		else if (State == PlayerState::Hero)
		{
			PlayerFSM.ChangeState("Hero");
		}
		else if (State == PlayerState::UnitPos)
		{
			PlayerFSM.ChangeState("UnitPos");
		}
	},
	.End = [this]()
	{

	}
	});
}

void PlayManager::CallReinforcementStateInit()
{
	PlayerFSM.CreateState({
	.Name = "CallReinforcement",
	.Start = [this]()
	{

	},
	.Update = [this](float _DeltaTime)
	{
		if (State == PlayerState::Idle)
		{
			PlayerFSM.ChangeState("Idle");
		}
		else if (State == PlayerState::RainOfFire)
		{
			PlayerFSM.ChangeState("RainOfFire");
		}
		else if (State == PlayerState::Hero)
		{
			PlayerFSM.ChangeState("Hero");
		}
		else if (State == PlayerState::UnitPos)
		{
			PlayerFSM.ChangeState("UnitPos");
		}
	},
	.End = [this]()
	{

	}
		});
}

void PlayManager::HeroStateInit()
{
	PlayerFSM.CreateState({
	.Name = "Hero",
	.Start = [this]()
	{

	},
	.Update = [this](float _DeltaTime)
	{
		if (State == PlayerState::Idle)
		{
			PlayerFSM.ChangeState("Idle");
		}
		else if (State == PlayerState::RainOfFire)
		{
			PlayerFSM.ChangeState("RainOfFire");
		}
		else if (State == PlayerState::CallReinforcement)
		{
			PlayerFSM.ChangeState("CallReinforcement");
		}
		else if (State == PlayerState::UnitPos)
		{
			PlayerFSM.ChangeState("UnitPos");
		}
	},
	.End = [this]()
	{

	}
		});
}

void PlayManager::TowerStateInit()
{
	PlayerFSM.CreateState({
	.Name = "Tower",
	.Start = [this]()
	{

	},
	.Update = [this](float _DeltaTime)
	{

	},
	.End = [this]()
	{

	}
		});
}

void PlayManager::UnitPosStateInit()
{
	PlayerFSM.CreateState({
	.Name = "UnitPos",
	.Start = [this]()
	{
	
	},
	.Update = [this](float _DeltaTime)
	{
		if (State == PlayerState::Idle)
		{
			PlayerFSM.ChangeState("Idle");
		}
		else if (State == PlayerState::RainOfFire)
		{
			PlayerFSM.ChangeState("RainOfFire");
		}
		else if (State == PlayerState::CallReinforcement)
		{
			PlayerFSM.ChangeState("CallReinforcement");
		}
		else if (State == PlayerState::Hero)
		{
			PlayerFSM.ChangeState("Hero");
		}
	},
	.End = [this]()
	{
	
	}
		});
}

