#include "PrecompileHeader.h"
#include "PauseButton.h"

#include <GameEngineCore\GameEngineUIRenderer.h>
#include "_101UIRenderer.h"
#include "PlayStageLevel.h"

PauseButton::PauseButton()
{

}

PauseButton::~PauseButton()
{

}

void PauseButton::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_1);
	Render->GetTransform()->SetWorldScale(PauseButtonScale);

	SetTextureName("PauseButton_Release.png", "PauseButton_Hover.png", "PauseButton_Hover.png");
	SetEvent([this]()
		{
			PlayStageLevel::MainPalyStage->PauseSwitch();
		});
}

void PauseButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
}
