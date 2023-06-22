#include "PrecompileHeader.h"
#include "MousePointer.h"

#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include <GameEngineCore\GameEngineCollision.h>
#include "PlayStageLevel.h"
#include "PlayManager.h"
#include "StageBg.h"
#include "RainOfFire.h"
#include "CallReinforcement.h"
#include "UpgradeTowerUI.h"
#include "Melee_Tower.h"
#include "Hero_RallyPoint.h"
#include "PlayStageUI.h"

void MousePointer::ReleaseStateInit()
{
	MouseFSM.CreateState({
		.Name = "Release"
		,.Start = [this]()
		{
			MousePointerRenderer->ChangeAnimation("Release");
		}
		,.Update = [this](float _DeltaTime)
		{
			if (PlayManager::MainPlayer->GetState() == PlayerState::RainOfFire)
			{
				State = MouseState::RainOfFire;
				MouseFSM.ChangeState("RainOfFire");
				return;
			}

			if (PlayManager::MainPlayer->GetState() == PlayerState::CallReinforcement)
			{
				State = MouseState::CallReinforcement;
				MouseFSM.ChangeState("CallReinforcement");
				return;
			}

			if (PlayManager::MainPlayer->GetState() == PlayerState::UnitPos)
			{
				State = MouseState::UnitPos;
				MouseFSM.ChangeState("UnitPos");
				return;
			}

			if (PlayManager::MainPlayer->GetState() == PlayerState::Hero)
			{
				State = MouseState::Hero;
				MouseFSM.ChangeState("Hero");
				return;
			}

			if (GameEngineInput::IsDown("EngineMouseLeft"))
			{
				State = MouseState::Press;
				MouseFSM.ChangeState("Press");
				return;
			}
		}
		,.End = [this]()
		{

		}
		});
}

void MousePointer::PressStateInit()
{
	MouseFSM.CreateState({
	.Name = "Press"
	,.Start = [this]()
	{
		MousePointerRenderer->ChangeAnimation("Press");
	}
	,.Update = [this](float _DeltaTime)
	{
		if (PlayManager::MainPlayer->GetState() == PlayerState::RainOfFire)
		{
			State = MouseState::RainOfFire;
			MouseFSM.ChangeState("RainOfFire");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::CallReinforcement)
		{
			State = MouseState::CallReinforcement;
			MouseFSM.ChangeState("CallReinforcement");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::UnitPos)
		{
			State = MouseState::UnitPos;
			MouseFSM.ChangeState("UnitPos");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::Hero)
		{
			State = MouseState::Hero;
			MouseFSM.ChangeState("Hero");
			return;
		}

		if (GameEngineInput::IsUp("EngineMouseLeft"))
		{
			State = MouseState::Release;
			MouseFSM.ChangeState("Release");
			return;
		}
	}
	,.End = [this]()
	{

	}
		});
}

void MousePointer::RainOfFireStateInit()
{
	MouseFSM.CreateState({
	.Name = "RainOfFire"
	,.Start = [this]()
	{
		MousePointerRenderer->ChangeAnimation("RainOfFire");
	}
	,.Update = [this](float _DeltaTime)
	{
		if (PlayManager::MainPlayer->GetState() == PlayerState::CallReinforcement)
		{
			State = MouseState::CallReinforcement;
			MouseFSM.ChangeState("CallReinforcement");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::Idle)
		{
			State = MouseState::Release;
			MouseFSM.ChangeState("Release");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::UnitPos)
		{
			State = MouseState::UnitPos;
			MouseFSM.ChangeState("UnitPos");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::Hero)
		{
			State = MouseState::Hero;
			MouseFSM.ChangeState("Hero");
			return;
		}

		if (GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (!IsThereMouseOntheColMap())
			{
				RainOfFire::CastingSpell(GetLevel(), GetIngameMousePosRef());
			}
			PlayManager::MainPlayer->SetState(PlayerState::Idle);
		}
		else if (GameEngineInput::IsUp("EngineMouseRight"))
		{
			PlayManager::MainPlayer->SetState(PlayerState::Idle);
		}
	}
	,.End = [this]()
	{

	}
		});
}

void MousePointer::CallReinforcementStateInit()
{
	MouseFSM.CreateState({
	.Name = "CallReinforcement"
	,.Start = [this]()
	{
		MousePointerRenderer->ChangeAnimation("CallReinforcement");
	}
	,.Update = [this](float _DeltaTime)
	{
		if (PlayManager::MainPlayer->GetState() == PlayerState::RainOfFire)
		{
			State = MouseState::RainOfFire;
			MouseFSM.ChangeState("RainOfFire");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::Idle)
		{
			State = MouseState::Release;
			MouseFSM.ChangeState("Release");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::UnitPos)
		{
			State = MouseState::UnitPos;
			MouseFSM.ChangeState("UnitPos");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::Hero)
		{
			State = MouseState::Hero;
			MouseFSM.ChangeState("Hero");
			return;
		}

		if (GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (!MousePointer::MainMouse->IsThereMouseOntheColMap())
			{
				CallReinforcement::CastingSpell(GetLevel(), MousePointer::MainMouse->GetIngameMousePosRef(), static_cast<FighterEnum>(static_cast<int>(FighterEnum::Reinforce) + PlayManager::MainPlayer->GetData().ReinforceLevel + 1));
			}
			PlayManager::MainPlayer->SetState(PlayerState::Idle);
		}
		else if (GameEngineInput::IsUp("EngineMouseRight"))
		{
			PlayManager::MainPlayer->SetState(PlayerState::Idle);
		}
	}
	,.End = [this]()
	{

	}
		});
}

void MousePointer::HeroStateInit()
{
	MouseFSM.CreateState({
	.Name = "Hero"
	,.Start = [this]()
	{
		MousePointerRenderer->ChangeAnimation("UnitSelect");
	}
	,.Update = [this](float _DeltaTime)
	{
		if (PlayManager::MainPlayer->GetState() == PlayerState::RainOfFire)
		{
			State = MouseState::RainOfFire;
			MouseFSM.ChangeState("RainOfFire");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::CallReinforcement)
		{
			State = MouseState::CallReinforcement;
			MouseFSM.ChangeState("CallReinforcement");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::Idle)
		{
			State = MouseState::Release;
			MouseFSM.ChangeState("Release");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::UnitPos)
		{
			State = MouseState::UnitPos;
			MouseFSM.ChangeState("UnitPos");
			return;
		}

		if (GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (/*!MousePointer::MainMouse->IsThereMouseOntheColMap()*/true)
			{
				PlayManager::MainPlayer->GetHero().lock()->SetRallyPos(MousePointer::GetIngameMousePosRef());
			}
			PlayManager::MainPlayer->SetState(PlayerState::Idle);
		}
		else if (GameEngineInput::IsUp("EngineMouseRight"))
		{
			PlayManager::MainPlayer->SetState(PlayerState::Idle);
		}
	}
	,.End = [this]()
	{

	}
		});
}

void MousePointer::UnitPosStateInit()
{
	MouseFSM.CreateState({
	.Name = "UnitPos"
	,.Start = [this]()
	{
		MousePointerRenderer->ChangeAnimation("UnitSelect");
	}
	,.Update = [this](float _DeltaTime)
	{
		if (PlayManager::MainPlayer->GetState() == PlayerState::RainOfFire)
		{
			State = MouseState::RainOfFire;
			MouseFSM.ChangeState("RainOfFire");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::CallReinforcement)
		{
			State = MouseState::CallReinforcement;
			MouseFSM.ChangeState("CallReinforcement");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::Idle)
		{
			State = MouseState::Release;
			MouseFSM.ChangeState("Release");
			return;
		}

		if (PlayManager::MainPlayer->GetState() == PlayerState::Hero)
		{
			State = MouseState::Hero;
			MouseFSM.ChangeState("Hero");
			return;
		}

		Melee_Tower* Tower = PlayManager::MainPlayer->SelectedMeleeTower;
		if (Tower->SetRallyMod && GameEngineInput::IsUp("EngineMouseLeft"))
		{
			Tower->SetRally();
			PlayManager::SelectedMeleeTower = nullptr;
			PlayManager::MainPlayer->SetState(PlayerState::Idle);
		}
	}
	,.End = [this]()
	{
	
	}
		});
}

void MousePointer::InvalidStateInit()
{
	MouseFSM.CreateState({
	.Name = "Invalid"
	,.Start = [this]()
	{

	}
	,.Update = [this](float _DeltaTime)
	{

	}
	,.End = [this]()
	{

	}
		});
}