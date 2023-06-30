#include "PrecompileHeader.h"
#include "RetryButton.h"

#include <GameEngineCore\GameEngineUIRenderer.h>
#include "UIFontRenderer.h"


RetryButton::RetryButton()
{

}

RetryButton::~RetryButton()
{

}

void RetryButton::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_1);
	Render->GetTransform()->SetWorldScale(Scale);
	SetTextureName("RetryButton_Release.png", "RetryButton_Hover.png", "RetryButton_Hover.png");

	ChainRender = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_0);
	ChainRender->GetTransform()->SetWorldScale(ChainRenderScale);
	ChainRender->GetTransform()->SetLocalPosition(ChainRenderLocPos);
	ChainRender->SetTexture("UIChain.png");
	ChainRender->Off();

	FontRender = CreateComponent<UIFontRenderer>(UIRenderOrder::StageUI_2);
	FontRender->SetFont(Font);
	FontRender->SetScale(FontScale);
	FontRender->SetFontFlag(FW1_CENTER);
	FontRender->SetColor(FontColor);
	FontRender->SetText(Continue);
	FontRender->GetTransform()->SetLocalPosition(FontLocPos);
}

void RetryButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
	if (GetTransform()->GetLocalPosition().y <= -300 && !ChainRender->IsUpdate())
	{
		ChainRender->On();
	}

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
