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
	ResultButton->GetTransform()->SetWorldPosition(_UI->GetTransform()->GetWorldPosition());
	ResultButton->GetTransform()->SetParent(_UI->GetTransform());
	ResultButton->SetEvent([_UI]()
		{
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
