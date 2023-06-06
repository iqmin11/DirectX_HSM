#include "PrecompileHeader.h"
#include "TowerButton.h"

#include <GameEngineCore/GameEngineLevel.h>
#include "BaseTower.h"
#include "UpgradeTowerUI.h"

TowerButton::TowerButton()
{

}

TowerButton::~TowerButton()
{

}

std::shared_ptr<TowerButton> TowerButton::CreateButton(BaseTower* _ParentTower)
{
	std::shared_ptr<TowerButton> ResultTowerButton = _ParentTower->GetLevel()->CreateActor<TowerButton>();
	ResultTowerButton->GetTransform()->SetWorldPosition(_ParentTower->GetTransform()->GetWorldPosition());
	ResultTowerButton->SetParentActor(_ParentTower);
	ResultTowerButton->SetEvent(
		[_ParentTower]()
		{
			_ParentTower->UpgradeUI->OnUI();
		});
	return ResultTowerButton;
}

void TowerButton::Start()
{
	ContentsButton::Start();
	GetTransform()->SetWorldScale(Scale);
	ReleaseTextureName = "Release.bmp";
	HoverTextureName = "Hover.bmp";
	PressTextureName = "Press.bmp";
}

void TowerButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
}
