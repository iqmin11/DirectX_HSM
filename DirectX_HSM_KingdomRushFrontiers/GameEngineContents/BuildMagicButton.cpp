#include "PrecompileHeader.h"
#include "BuildMagicButton.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "BuildTowerUI.h"
#include "BuildArea.h"

BuildMagicButton::BuildMagicButton()
{

}

BuildMagicButton::~BuildMagicButton()
{

}

std::shared_ptr<BuildMagicButton> BuildMagicButton::CreateButton(BuildTowerUI* _UI)
{
	std::shared_ptr<BuildMagicButton> ResultButton = _UI->GetLevel()->CreateActor<BuildMagicButton>();
	float4 UIPos = _UI->GetTransform()->GetWorldPosition();
	ResultButton->GetTransform()->SetWorldPosition({ UIPos.x, UIPos.y });
	ResultButton->SetParentActor(_UI);
	ResultButton->SetEvent([_UI]()
		{
			if (_UI->GetState() == BaseTowerUIState::Start)
			{
				return;
			}
			_UI->OffUI();
			_UI->GetParentArea()->CreateMagicTower();
		});
	return ResultButton;
}

void BuildMagicButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0003.png";
	HoverTextureName = "main_icons_0003.png";
	PressTextureName = "main_icons_0003.png";
}

void BuildMagicButton::Update(float _DeltaTime)
{
	BaseBuildButton::Update(_DeltaTime);
}
