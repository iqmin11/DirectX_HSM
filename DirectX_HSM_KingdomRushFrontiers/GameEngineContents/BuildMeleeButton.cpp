#include "PrecompileHeader.h"
#include "BuildMeleeButton.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "BuildTowerUI.h"
#include "BuildArea.h"

BuildMeleeButton::BuildMeleeButton()
{

}

BuildMeleeButton::~BuildMeleeButton()
{

}

std::shared_ptr<BuildMeleeButton> BuildMeleeButton::CreateButton(BuildTowerUI* _UI)
{
	std::weak_ptr<BuildMeleeButton> ResultButton(_UI->GetLevel()->CreateActor<BuildMeleeButton>());
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
			ResultButton.lock()->ParentUI->GetParentArea()->CreateMeleeTower();
			PlayManager::MainPlayer->Gold -= ResultButton.lock()->GetPrice();
		});
	return ResultButton.lock();
}

void BuildMeleeButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0002.png";
	HoverTextureName = "main_icons_0002.png";
	PressTextureName = "main_icons_0002.png";
	InvalidTextureName = "main_icons_disabled_0002.png";

	TowerData LocalData;
	LocalData.SetData(TowerEnum::MeleeTower_Level1);
	SetPrice(LocalData.BuildCost);
}

void BuildMeleeButton::Update(float _DeltaTime)
{
	BaseBuildButton::Update(_DeltaTime);
}
