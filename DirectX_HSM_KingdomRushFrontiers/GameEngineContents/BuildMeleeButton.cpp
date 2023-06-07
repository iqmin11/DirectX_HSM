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
	std::shared_ptr<BuildMeleeButton> ResultButton = _UI->GetLevel()->CreateActor<BuildMeleeButton>();
	ResultButton->GetTransform()->SetWorldPosition(_UI->GetTransform()->GetWorldPosition());
	ResultButton->SetParentActor(_UI);
	ResultButton->SetEvent([_UI]()
		{
			if (_UI->GetState() == BaseTowerUIState::Start)
			{
				return;
			}
			_UI->OffUI();
			_UI->GetParentArea()->CreateMeleeTower();
		});
	return ResultButton;
}

void BuildMeleeButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0002.png";
	HoverTextureName = "main_icons_0002.png";
	PressTextureName = "main_icons_0002.png";
}

void BuildMeleeButton::Update(float _DeltaTime)
{
	BaseBuildButton::Update(_DeltaTime);
}
