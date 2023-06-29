#include "PrecompileHeader.h"
#include "RallyButton.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "UpgradeTowerUI_ex.h"
#include "BaseTower.h"
#include "Melee_Tower.h"
#include "PlayManager.h"
#include "PlayStageLevel.h"

RallyButton::RallyButton()
{

}

RallyButton::~RallyButton()
{

}

std::shared_ptr<RallyButton> RallyButton::CreateButton(UpgradeTowerUI_ex* _UI)
{
	std::weak_ptr<RallyButton> ResultButton(_UI->GetLevel()->CreateActor<RallyButton>());
	float4 UIPos = _UI->GetTransform()->GetWorldPosition();
	ResultButton.lock()->GetTransform()->SetWorldPosition({ UIPos.x, UIPos.y, 0.f });
	ResultButton.lock()->SetParentActor(_UI);
	ResultButton.lock()->SetEvent([ResultButton]()
		{
			UpgradeTowerUI* ParentUI = dynamic_cast<UpgradeTowerUI*>(ResultButton.lock()->GetParentActor());
			if (ParentUI->GetState() == BaseTowerUIState::Start)
			{
				return;
			}
			dynamic_cast<Melee_Tower*>(ParentUI->GetParentTower())->SetRallyMod = true;
			PlayManager::MainPlayer->SetState(PlayerState::UnitPos);
			PlayManager::SelectedMeleeTower = dynamic_cast<Melee_Tower*>(ParentUI->GetParentTower());
			ResultButton.lock()->State = ButtonState::Release; //임시방편.. 사실 모든 버튼은 꺼질때 Release상태가 되어야함.
			ParentUI->OffUI();
		});
	return ResultButton.lock();
}

void RallyButton::Start()
{
	ContentsButton::Start();
	ButtonGlow = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::TowerUIButton);
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::TowerUIButton);
	GetTransform()->SetWorldScale(Scale);
	ReleaseTextureName = "sub_icons_0001.png";
	HoverTextureName = "sub_icons_0001.png";
	PressTextureName = "sub_icons_0001.png";

	ButtonGlow->SetTexture("CircleButtonsGlow.png");
	ButtonGlow->GetTransform()->SetWorldScale(GlowScale);
	ButtonGlow->Off();
}

void RallyButton::Update(float _DeltaTime)
{
	if (GetLevel()->DynamicThis<PlayStageLevel>()->IsPause)
	{
		return;
	}

	ContentsButton::Update(_DeltaTime);
	if (State == ButtonState::Release)
	{
		if (ButtonGlow->IsUpdate())
		{
			ButtonGlow->Off();
		}
	}
	else
	{
		if (!ButtonGlow->IsUpdate())
		{
			ButtonGlow->On();
		}
	}
}
