#include "PrecompileHeader.h"
#include "SelectStageWindow.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "StageStartButton.h"
#include "ExitButton.h"
#include "_101UIRenderer.h"
#include "_101UIFontRenderer.h"

SelectStageWindow* SelectStageWindow::MainSelectWindow = nullptr;

SelectStageWindow::SelectStageWindow()
{
	MainSelectWindow = this;
}

SelectStageWindow::~SelectStageWindow()
{

}

void SelectStageWindow::Start()
{
	WindowBg = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_0);
	WindowBg->SetTexture("SelectStageBook.png");
	WindowBg->GetTransform()->SetWorldScale(BgScale);

	StagePreview = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_1);
	//StagePreview->SetTexture("Preview_0.png");
	StagePreview->GetTransform()->SetWorldScale(PreviewScale);
	StagePreview->GetTransform()->SetLocalPosition(PreviewLocPos);

	WornOutEffect = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_2);
	WornOutEffect->SetTexture("WornEffect.png");
	WornOutEffect->GetTransform()->SetWorldScale(EffectScale);
	WornOutEffect->GetTransform()->SetLocalPosition(PreviewLocPos);

	AcStageStartButton = StageStartButton::CreateButton(this);
	AcStageStartButton->GetTransform()->SetLocalPosition(StartButtonLocPos);

	ExitWindowButton = ExitButton::CreateButton(this);
	ExitWindowButton->GetTransform()->SetLocalPosition(ExitButtonLocPos);
	
	Off();
}

void SelectStageWindow::Update(float _DeltaTime)
{
	StagePreview->SetTexture("Preview_" + std::to_string(SelectedStage) + ".png");
}
