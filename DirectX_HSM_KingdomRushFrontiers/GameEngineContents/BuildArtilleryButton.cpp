#include "PrecompileHeader.h"
#include "BuildArtilleryButton.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "BuildTowerUI.h"
#include "BuildArea.h"
#include <GameEngineCore\GameEngineUIRenderer.h>

BuildArtilleryButton::BuildArtilleryButton()
{

}

BuildArtilleryButton::~BuildArtilleryButton()
{

}

std::shared_ptr<BuildArtilleryButton> BuildArtilleryButton::CreateButton(BuildTowerUI* _UI)
{
	std::weak_ptr<BuildArtilleryButton> ResultButton(_UI->GetLevel()->CreateActor<BuildArtilleryButton>());
	BuildTowerUI* Parent = ResultButton.lock()->ParentUI = _UI;
	float4 UIPos = Parent->GetTransform()->GetWorldPosition();
	ResultButton.lock()->GetTransform()->SetWorldPosition({ UIPos.x, UIPos.y });
	ResultButton.lock()->SetParentActor(Parent);
	ResultButton.lock()->SetEvent([ResultButton]()
		{
			if (ResultButton.lock()->ParentUI->GetState() == BaseTowerUIState::Start || !ResultButton.lock()->IsHaveEnoughGold())
			{
				return;
			}
			ResultButton.lock()->ParentUI->OffUI();
			ResultButton.lock()->ParentUI->GetParentArea()->CreateArtilleryTower();
			PlayManager::MainPlayer->Gold -= ResultButton.lock()->GetPrice();
		});
	return ResultButton.lock();
}

void BuildArtilleryButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0004.png";
	HoverTextureName = "main_icons_0004.png";
	PressTextureName = "main_icons_0004.png";
	InvalidTextureName = "main_icons_disabled_0004.png";

	TowerData LocalData;
	LocalData.SetData(TowerEnum::ArtilleryTower_Level1);
	SetPrice(LocalData.BuildCost);
}

void BuildArtilleryButton::Update(float _DeltaTime)
{
	BaseBuildButton::Update(_DeltaTime);
}


