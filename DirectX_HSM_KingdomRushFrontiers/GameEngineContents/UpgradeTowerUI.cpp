#include "PrecompileHeader.h"
#include "UpgradeTowerUI.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BaseTower.h"
#include "UpgradeTowerButton.h"
#include "SellButton.h"

UpgradeTowerUI::UpgradeTowerUI()
{

}

UpgradeTowerUI::~UpgradeTowerUI()
{

}

std::shared_ptr<UpgradeTowerUI> UpgradeTowerUI::CreateUpgradeTowerUI(BaseTower* _ParentTower)
{
	std::shared_ptr<UpgradeTowerUI> ResultUI = _ParentTower->GetLevel()->CreateActor<UpgradeTowerUI>();
	float4 ParentPos = _ParentTower->GetTransform()->GetWorldPosition();
	ResultUI->GetTransform()->SetWorldPosition({ParentPos.x, ParentPos.y + 15, 0});
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
	AcSellButton = SellButton::CreateButton(this);
	AcSellButton->GetTransform()->SetLocalPosition(SellButtonLocPos);
}

void UpgradeTowerUI::Update(float _DeltaTime)
{
	BaseTowerUI::Update(_DeltaTime);
	if (GameEngineInput::IsUp("EngineMouseRight"))
	{
		OffUI();
	}

	if (UpdatedUI != this && UpdatedUI != nullptr)
	{
		OffUI();
	}
}


