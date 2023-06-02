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

int BuildTowerUI::UpdateCount = 0;
BuildTowerUI* BuildTowerUI::UpdatedUI = nullptr;

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
	RingRender = CreateComponent<GameEngineUIRenderer>();
	RingRender->SetTexture("gui_ring.png");
	RingRender->GetTransform()->SetWorldScale(RingRenderScale);

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
		OffBuildUI();
	}

	if (UpdatedUI != this && UpdatedUI != nullptr)
	{
		OffBuildUI();
	}
}

void BuildTowerUI::UpdateStart()
{
	UpdatedUI = this;
	++UpdateCount;
}

void BuildTowerUI::UpdateEnd()
{
	--UpdateCount;
	if (UpdateCount == 0)
	{
		UpdatedUI = nullptr;
	}
}

void BuildTowerUI::OnBuildUI()
{
	On();
	UpdateStart();
}

void BuildTowerUI::OffBuildUI()
{
	Off();
	UpdateEnd();
}