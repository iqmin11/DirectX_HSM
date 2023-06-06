#include "PrecompileHeader.h"
#include "BuildTowerUI.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BuildArea.h"
#include "BuildRangedButton.h"
#include "BuildMeleeButton.h"
#include "BuildMagicButton.h"
#include "BuildArtilleryButton.h"

BuildTowerUI::BuildTowerUI()
{

}

BuildTowerUI::~BuildTowerUI()
{

}

std::shared_ptr<BuildTowerUI> BuildTowerUI::CreateBuildTowerUI(BuildArea* _ParentArea)
{
	std::shared_ptr<BuildTowerUI> ResultUI = _ParentArea->GetLevel()->CreateActor<BuildTowerUI>();
	ResultUI->GetTransform()->SetWorldPosition(_ParentArea->GetTransform()->GetWorldPosition());
	ResultUI->ParentArea = _ParentArea;
	ResultUI->GetTransform()->SetParent(_ParentArea->GetTransform());
	ResultUI->Off();
	return ResultUI;
}

void BuildTowerUI::Start()
{
	BaseTowerUI::Start();
	AcBuildRangedButton = BuildRangedButton::CreateButton(this);
	AcBuildRangedButton->GetTransform()->SetLocalPosition(Button0LocPos);
	AcBuildMeleeButton = BuildMeleeButton::CreateButton(this);
	AcBuildMeleeButton->GetTransform()->SetLocalPosition(Button1LocPos);
	AcBuildMagicButton = BuildMagicButton::CreateButton(this);
	AcBuildMagicButton->GetTransform()->SetLocalPosition(Button2LocPos);
	AcBuildArtilleryButton = BuildArtilleryButton::CreateButton(this);
	AcBuildArtilleryButton->GetTransform()->SetLocalPosition(Button3LocPos);
}

void BuildTowerUI::Update(float _DeltaTime)
{
	if (GameEngineInput::IsUp("EngineMouseRight"))
	{
		OffUI();
	}

	if (UpdatedUI != this && UpdatedUI != nullptr)
	{
		OffUI();
	}
}