#include "PrecompileHeader.h"
#include "ContinueButton.h"

#include <GameEngineCore\GameEngineCore.h>
#include "_101UIFontRenderer.h"
#include "_101UIRenderer.h"

ContinueButton::ContinueButton()
{

}

ContinueButton::~ContinueButton()
{

}

void ContinueButton::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_4);
	Render->GetTransform()->SetWorldScale(Scale);
	SetTextureName("ContinueButton_Release.png", "ContinueButton_Hover.png", "ContinueButton_Hover.png");

	ChainRender = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_3);
	ChainRender->GetTransform()->SetWorldScale(ChainRenderScale);
	ChainRender->GetTransform()->SetLocalPosition(ChainRenderLocPos);
	ChainRender->SetTexture("UIChain.png");

	FontRender = CreateComponent<_101UIFontRenderer>(UIRenderOrder::StageUI_5);
	FontRender->SetFont(Font);
	FontRender->SetScale(FontScale);
	FontRender->SetFontFlag(FW1_CENTER);
	FontRender->SetColor(FontColor);
	FontRender->SetText(Continue);
	FontRender->GetTransform()->SetLocalPosition(FontLocPos);
}

void ContinueButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
	if (GetState() == ButtonState::Press)
	{
		Render->GetTransform()->SetWorldScale(Scale * 0.95f);
		FontRender->SetScale(FontScale * 0.95f);
	}
	else
	{
		if (Render->GetTransform()->GetWorldScale() != Scale)
		{
			Render->GetTransform()->SetWorldScale(Scale * 1.f);
			FontRender->SetScale(FontScale);
		}
	}
}
