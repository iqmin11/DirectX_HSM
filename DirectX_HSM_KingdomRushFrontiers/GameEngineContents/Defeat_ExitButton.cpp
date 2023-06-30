#include "PrecompileHeader.h"
#include "Defeat_ExitButton.h"

#include "_101UIFontRenderer.h"
#include "_101UIRenderer.h"

Defeat_ExitButton::Defeat_ExitButton()
{

}

Defeat_ExitButton::~Defeat_ExitButton()
{

}

void Defeat_ExitButton::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<_101UIRenderer>(UIRenderOrder::StageUI_1);
	Render->GetTransform()->SetWorldScale(Scale);
	SetTextureName("DefeatButtons_Release.png", "DefeatButtons_Hover.png", "DefeatButtons_Hover.png");

	FontRender = CreateComponent<_101UIFontRenderer>(UIRenderOrder::StageUI_2);
	FontRender->SetFont(Font);
	FontRender->SetScale(FontScale);
	FontRender->SetFontFlag(FW1_CENTER);
	FontRender->SetColor(FontColor);
	FontRender->SetText(Continue);
	FontRender->GetTransform()->SetLocalPosition(FontLocPos);
}

void Defeat_ExitButton::Update(float _DeltaTime)
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
