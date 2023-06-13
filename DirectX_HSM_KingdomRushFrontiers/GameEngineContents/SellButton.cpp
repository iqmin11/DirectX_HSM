#include "PrecompileHeader.h"
#include "SellButton.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "UpgradeTowerUI.h"
#include "BaseTower.h"

SellButton::SellButton()
{

}

SellButton::~SellButton()
{

}

std::shared_ptr<SellButton> SellButton::CreateButton(UpgradeTowerUI* _UI)
{
	std::weak_ptr<SellButton> ResultButton(_UI->GetLevel()->CreateActor<SellButton>());
	float4 UIPos = _UI->GetTransform()->GetWorldPosition();
	ResultButton.lock()->GetTransform()->SetWorldPosition({UIPos.x, UIPos.y, 0.f});
	ResultButton.lock()->SetParentActor(_UI);
	ResultButton.lock()->SetEvent([ResultButton]()
		{
			UpgradeTowerUI* ParentUI = dynamic_cast<UpgradeTowerUI*>(ResultButton.lock()->GetParentActor());
			if (ParentUI->GetState() == BaseTowerUIState::Start)
			{
				return;
			}
			ParentUI->OffUI();
			ParentUI->GetParentTower()->SellTower();
		});
	return ResultButton.lock();
}

void SellButton::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::TowerUIButton);
	GetTransform()->SetWorldScale(Scale);
	ReleaseTextureName = "ico_sell_0001.png";
	HoverTextureName = "ico_sell_0001.png";
	PressTextureName = "ico_sell_0001.png";
}

void SellButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
}
