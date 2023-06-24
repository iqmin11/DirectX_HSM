#include "PrecompileHeader.h"
#include "UpgradeTowerUI_ex.h"

#include <GameEngineCore/GameEngineLevel.h>
#include "RallyButton.h"
#include "BaseTower.h"

UpgradeTowerUI_ex::UpgradeTowerUI_ex()
{

}

UpgradeTowerUI_ex::~UpgradeTowerUI_ex()
{

}

std::shared_ptr<UpgradeTowerUI_ex> UpgradeTowerUI_ex::CreateUpgradeTowerUI(BaseTower* _ParentTower)
{
	std::shared_ptr<UpgradeTowerUI_ex> ResultUI = _ParentTower->GetLevel()->CreateActor<UpgradeTowerUI_ex>();
	float4 ParentPos = _ParentTower->GetTransform()->GetWorldPosition();
	ResultUI->GetTransform()->SetWorldPosition({ ParentPos.x, ParentPos.y + 15, 0 });
	ResultUI->ParentActor = _ParentTower;
	ResultUI->GetTransform()->SetParent(_ParentTower->GetTransform());
	ResultUI->Off();
	return ResultUI;
}

void UpgradeTowerUI_ex::Start()
{
	UpgradeTowerUI::Start();
	AcRallyButton = RallyButton::CreateButton(this);
	AcRallyButton->GetTransform()->SetLocalPosition(RallyButtonLocPos);
}

void UpgradeTowerUI_ex::Update(float _DeltaTime)
{
	UpgradeTowerUI::Update(_DeltaTime);
}
