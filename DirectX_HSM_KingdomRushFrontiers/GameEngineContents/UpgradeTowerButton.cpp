#include "PrecompileHeader.h"
#include "UpgradeTowerButton.h"

#include <GameEngineCore/GameEngineLevel.h>
#include "UpgradeTowerUI.h"
#include "BaseTower.h"

UpgradeTowerButton::UpgradeTowerButton()
{

}

UpgradeTowerButton::~UpgradeTowerButton()
{

}

std::shared_ptr<UpgradeTowerButton> UpgradeTowerButton::CreateButton(UpgradeTowerUI* _UI)
{
	std::weak_ptr<UpgradeTowerButton> ResultButton(_UI->GetLevel()->CreateActor<UpgradeTowerButton>());
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
			ResultButton.lock()->ParentUI->GetParentTower()->ChangeTower(ResultButton.lock()->ReturnUpgradeTowerEnum());
		});
	return ResultButton.lock();
}

void UpgradeTowerButton::Start()
{
	ContentsButton::Start();
	GetTransform()->SetWorldScale(Scale);
	ReleaseTextureName = "main_icons_0005.png";
	HoverTextureName = "main_icons_0005.png";
	PressTextureName = "main_icons_0005.png";
}

void UpgradeTowerButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
}

TowerEnum UpgradeTowerButton::ReturnUpgradeTowerEnum()
{
	if (nullptr == ParentUI)
	{
		MsgAssert("ParentUI가 nullptr입니다")
	}

	TowerData Data = ParentUI->GetParentTower()->GetData();
	if (Data.Level >= 3)
	{
		MsgTextBox("아직 구현하지 않은 타워입니다");
		return static_cast<TowerEnum>(static_cast<int>(Data.TowerType) + Data.Level);
	}
	return static_cast<TowerEnum>(static_cast<int>(Data.TowerType) + Data.Level + 1);
}
