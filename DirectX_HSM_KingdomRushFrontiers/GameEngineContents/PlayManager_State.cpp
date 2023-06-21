#include "PrecompileHeader.h"
#include "PlayManager.h"

#include <GameEnginePlatform\GameEngineInput.h>
#include "MousePointer.h"
#include "RainOfFire.h"
#include "CallReinforcement.h"

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
		if (GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (!MousePointer::MainMouse->IsThereMouseOntheColMap())
			{
				RainOfFire::CastingSpell(GetLevel(), MousePointer::MainMouse->GetIngameMousePosRef());
			}
			State = PlayerState::Idle;
			PlayerFSM.ChangeState("Idle");
		}
		else if(GameEngineInput::IsUp("EngineMouseRight"))
		{
			State = PlayerState::Idle;
			PlayerFSM.ChangeState("Idle");
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
		if (GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (!MousePointer::MainMouse->IsThereMouseOntheColMap())
			{
				CallReinforcement::CastingSpell(GetLevel(), MousePointer::MainMouse->GetIngameMousePosRef(), static_cast<FighterEnum>(static_cast<int>(FighterEnum::Reinforce) + Data.ReinforceLevel + 1));
			}
			State = PlayerState::Idle;
			PlayerFSM.ChangeState("Idle");
		}
		else if (GameEngineInput::IsUp("EngineMouseRight"))
		{
			State = PlayerState::Idle;
			PlayerFSM.ChangeState("Idle");
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