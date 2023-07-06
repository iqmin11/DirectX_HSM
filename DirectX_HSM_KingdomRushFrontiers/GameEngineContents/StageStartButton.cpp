#include "PrecompileHeader.h"
#include "StageStartButton.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "_101UIRenderer.h"
#include "PlayStageLevel.h"
#include "WorldMapLevel.h"
#include "SelectStageWindow.h"

StageStartButton::StageStartButton()
{

}

StageStartButton::~StageStartButton()
{

}

std::shared_ptr<StageStartButton> StageStartButton::CreateButton(GameEngineActor* _Parent)
{
	std::weak_ptr<StageStartButton> LocButton(_Parent->GetLevel()->CreateActor<StageStartButton>());
	LocButton.lock()->GetTransform()->SetParent(_Parent->GetTransform());
	LocButton.lock()->SetParentActor(_Parent);
	LocButton.lock()->SetEvent([LocButton]()
		{
			PlayStageLevel::MainPalyStage->InitStage(SelectStageWindow::MainSelectWindow->GetSelectedStage());
			GameEngineCore::ChangeLevel("PlayStageLevel");
			LocButton.lock()->GetParentActor()->Off();
			WorldMapLevel::IsPause = false;
		});
	return LocButton.lock();
}

void StageStartButton::Start()
{
	Render = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_2);
	Render->GetTransform()->SetWorldScale(ButtonScale);
	SetTextureName("SelectButton_Release.png","SelectButton_Hover.png","SelectButton_Hover.png");
}
