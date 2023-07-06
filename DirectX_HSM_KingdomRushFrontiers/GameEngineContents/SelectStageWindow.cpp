#include "PrecompileHeader.h"
#include "SelectStageWindow.h"

#include <GameEngineCore\GameEngineLevel.h>
#include "StageStartButton.h"
#include "_101UIRenderer.h"
#include "_101UIFontRenderer.h"

SelectStageWindow::SelectStageWindow()
{

}

SelectStageWindow::~SelectStageWindow()
{

}

void SelectStageWindow::Start()
{
	WindowBg = CreateComponent<_101UIRenderer>(UIRenderOrder::Bg);
	WindowBg->SetTexture("SelectStageBook.png");
	WindowBg->GetTransform()->SetWorldScale(BgScale);

	StagePreview = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_0);
	StagePreview->SetTexture("Preview_0.png");
	StagePreview->GetTransform()->SetWorldScale(PreviewScale);
	StagePreview->GetTransform()->SetLocalPosition(PreviewLocPos);

	WornOutEffect = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_1);
	WornOutEffect->SetTexture("WornEffect.png");
	WornOutEffect->GetTransform()->SetWorldScale(EffectScale);
	WornOutEffect->GetTransform()->SetLocalPosition(PreviewLocPos);

	StageStartButton = StageStartButton::CreateButton(this);
	StageStartButton->GetTransform()->SetLocalPosition(StartButtonLocPos);
}

void SelectStageWindow::Update(float _DeltaTime)
{
}
