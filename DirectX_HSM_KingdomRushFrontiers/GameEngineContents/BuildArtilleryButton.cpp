#include "PrecompileHeader.h"
#include "BuildArtilleryButton.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "BuildTowerUI.h"
#include "BuildArea.h"

BuildArtilleryButton::BuildArtilleryButton()
{

}

BuildArtilleryButton::~BuildArtilleryButton()
{

}

std::shared_ptr<BuildArtilleryButton> BuildArtilleryButton::CreateButton(BuildTowerUI* _UI)
{
	std::shared_ptr<BuildArtilleryButton> ResultButton = _UI->GetLevel()->CreateActor<BuildArtilleryButton>();
	ResultButton->GetTransform()->SetWorldPosition(_UI->GetTransform()->GetWorldPosition());
	ResultButton->GetTransform()->SetParent(_UI->GetTransform());
	ResultButton->SetEvent([_UI]()
		{
			if (_UI->GetState() == BaseTowerUIState::Start)
			{
				return;
			}
			_UI->OffUI();
			_UI->GetParentArea()->CreateArtilleryTower();
		});
	return ResultButton;
}

void BuildArtilleryButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0004.png";
	HoverTextureName = "main_icons_0004.png";
	PressTextureName = "main_icons_0004.png";
}

void BuildArtilleryButton::Update(float _DeltaTime)
{
	BaseBuildButton::Update(_DeltaTime);
}
