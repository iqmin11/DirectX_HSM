#include "PrecompileHeader.h"
#include "BuildMagicButton.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "BuildTowerUI.h"
#include "BuildArea.h"
#include "PlayStageLevel.h"

BuildMagicButton::BuildMagicButton()
{

}

BuildMagicButton::~BuildMagicButton()
{

}

std::shared_ptr<BuildMagicButton> BuildMagicButton::CreateButton(BuildTowerUI* _UI)
{
	std::weak_ptr<BuildMagicButton> ResultButton(_UI->GetLevel()->CreateActor<BuildMagicButton>());
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
			ResultButton.lock()->ParentUI->GetParentArea()->CreateMagicTower();
			PlayManager::MainPlayer->Gold -= ResultButton.lock()->GetPrice();
		});
	return ResultButton.lock();
}

void BuildMagicButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0003.png";
	HoverTextureName = "main_icons_0003.png";
	PressTextureName = "main_icons_0003.png";
	InvalidTextureName = "main_icons_disabled_0003.png";

	TowerData LocalData;
	LocalData.SetData(TowerEnum::MagicTower_Level1);
	SetPrice(LocalData.BuildCost);
}

void BuildMagicButton::Update(float _DeltaTime)
{
	if (GetLevel()->DynamicThis<PlayStageLevel>()->IsPause)
	{
		return;
	}

	BaseBuildButton::Update(_DeltaTime);
}
