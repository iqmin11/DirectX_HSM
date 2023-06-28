#include "PrecompileHeader.h"
#include "ContinueButton.h"

#include <GameEngineCore\GameEngineUIRenderer.h>
#include "UIFontRenderer.h"

ContinueButton::ContinueButton()
{

}

ContinueButton::~ContinueButton()
{

}

void ContinueButton::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_1);
	Render->GetTransform()->SetWorldScale(Scale);
	SetTextureName("ContinueButton_Release.png", "ContinueButton_Hover.png", "ContinueButton_Hover.png");
	SetEvent([]()
		{

		});

	ChainRender = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_0);
	ChainRender->GetTransform()->SetWorldScale({172,99,1});
	ChainRender->GetTransform()->SetLocalPosition({0, 50});
	ChainRender->SetTexture("UIChain.png");

	FontRender = CreateComponent<UIFontRenderer>(UIRenderOrder::StageUI_2);
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
