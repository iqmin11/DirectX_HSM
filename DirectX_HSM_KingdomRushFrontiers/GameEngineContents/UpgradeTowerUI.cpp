#include "PrecompileHeader.h"
#include "UpgradeTowerUI.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BaseTower.h"
#include "UpgradeTowerButton.h"

UpgradeTowerUI::UpgradeTowerUI()
{

}

UpgradeTowerUI::~UpgradeTowerUI()
{

}

std::shared_ptr<UpgradeTowerUI> UpgradeTowerUI::CreateUpgradeTowerUI(BaseTower* _ParentTower)
{
	std::shared_ptr<UpgradeTowerUI> ResultUI = _ParentTower->GetLevel()->CreateActor<UpgradeTowerUI>();
	ResultUI->GetTransform()->SetWorldPosition(_ParentTower->GetTransform()->GetWorldPosition());
	ResultUI->ParentTower = _ParentTower;
	ResultUI->GetTransform()->SetParent(_ParentTower->GetTransform());
	ResultUI->Off();
	return ResultUI;
}

void UpgradeTowerUI::Start()
{
	BaseTowerUI::Start();
	AcUpgradeButton = UpgradeTowerButton::CreateButton(this);
	AcUpgradeButton->GetTransform()->SetLocalPosition(UpgradeButtonLocPos);
}

void UpgradeTowerUI::Update(float _DeltaTime)
{
	if (GameEngineInput::IsUp("EngineMouseRight"))
	{
		OffUI();
	}

	if (UpdatedUI != this && UpdatedUI != nullptr)
	{
		OffUI();
	}
}

