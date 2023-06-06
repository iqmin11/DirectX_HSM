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
	ResultButton->GetTransform()->SetWorldPosition(_UI->GetTransform()->GetWorldPosition());
	ResultButton->GetTransform()->SetParent(_UI->GetTransform());
	ResultButton->SetEvent([_UI]()
		{
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
