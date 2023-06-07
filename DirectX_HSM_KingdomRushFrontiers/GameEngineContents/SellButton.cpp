#include "PrecompileHeader.h"
#include "SellButton.h"

#include <GameEngineCore/GameEngineLevel.h>
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
	ResultButton.lock()->GetTransform()->SetWorldPosition(_UI->GetTransform()->GetWorldPosition());
	ResultButton.lock()->GetTransform()->SetParent(_UI->GetTransform());
	ResultButton.lock()->ParentUI = _UI;
	ResultButton.lock()->SetEvent([ResultButton]()
		{
			if (ResultButton.lock()->ParentUI->GetState() == BaseTowerUIState::Start)
			{
				return;
			}
			ResultButton.lock()->ParentUI->OffUI();
			ResultButton.lock()->ParentUI->GetParentTower()->SellTower();
		});
	return ResultButton.lock();
}

void SellButton::Start()
{
	ContentsButton::Start();
	GetTransform()->SetWorldScale(Scale);
	ReleaseTextureName = "ico_sell_0001.png";
	HoverTextureName = "ico_sell_0001.png";
	PressTextureName = "ico_sell_0001.png";
}

void SellButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
}
