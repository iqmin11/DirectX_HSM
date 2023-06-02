#include "PrecompileHeader.h"
#include "BuildTowerUI.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BuildArea.h"

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
	RingRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::Mob);
	RingRender->SetTexture("gui_ring.png");
	RingRender->GetTransform()->SetWorldScale(RingRenderScale);
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