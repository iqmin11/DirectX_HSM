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
	std::shared_ptr<BuildRangedButton> ResultButton = _UI->GetLevel()->CreateActor<BuildRangedButton>();
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
			_UI->GetParentArea()->CreateRangedTower();
		});
	return ResultButton;
}

void BuildRangedButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0001.png";
	HoverTextureName = "main_icons_0001.png";
	PressTextureName = "main_icons_0001.png";
}

void BuildRangedButton::Update(float _DeltaTime)
{
	BaseBuildButton::Update(_DeltaTime);
}
