#include "PrecompileHeader.h"
#include "BuildRangedButton.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "BuildTowerUI.h"
#include "BuildArea.h"

BuildRangedButton::BuildRangedButton()
{

}

BuildRangedButton::~BuildRangedButton()
{

}

std::shared_ptr<BuildRangedButton> BuildRangedButton::CreateButton(BuildTowerUI* _UI)
{
	std::weak_ptr<BuildRangedButton> ResultButton(_UI->GetLevel()->CreateActor<BuildRangedButton>());
	BuildTowerUI* Parent = ResultButton.lock()->ParentUI = _UI;
	float4 UIPos = Parent->GetTransform()->GetWorldPosition();
	ResultButton.lock()->GetTransform()->SetWorldPosition({ UIPos.x, UIPos.y });
	ResultButton.lock()->SetParentActor(Parent);
	ResultButton.lock()->SetEvent([ResultButton]()
		{
			if (ResultButton.lock()->ParentUI->GetState() == BaseTowerUIState::Start || !PlayManager::MainPlayer->DoIHaveEnoughGold(ResultButton.lock()->Price))
			{
				return;
			}
			ResultButton.lock()->ParentUI->OffUI();
			ResultButton.lock()->ParentUI->GetParentArea()->CreateRangedTower();
			PlayManager::MainPlayer->Gold -= ResultButton.lock()->GetPrice();
		});
	return ResultButton.lock();
}

void BuildRangedButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0001.png";
	HoverTextureName = "main_icons_0001.png";
	PressTextureName = "main_icons_0001.png";
	InvalidTextureName = "main_icons_disabled_0001.png";

	TowerData LocalData;
	LocalData.SetData(TowerEnum::RangedTower_Level1);
	SetPrice(LocalData.BuildCost);
}

void BuildRangedButton::Update(float _DeltaTime)
{
	BaseBuildButton::Update(_DeltaTime);
}
