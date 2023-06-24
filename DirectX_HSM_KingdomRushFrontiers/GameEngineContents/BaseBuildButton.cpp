#include "PrecompileHeader.h"
#include "BaseBuildButton.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

BaseBuildButton::BaseBuildButton()
{

}

BaseBuildButton::~BaseBuildButton()
{

}

void BaseBuildButton::Start()
{
	ContentsButton::Start();
	ButtonGlow = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::TowerUIButton);
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::TowerUIButton);
	GetTransform()->SetWorldScale(Scale);
	ButtonGlow->SetTexture("ButtonsGlow.png");
	ButtonGlow->GetTransform()->SetWorldScale(GlowScale);
	ButtonGlow->Off();
}

void BaseBuildButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
	if (State == ButtonState::Release)
	{
		if (ButtonGlow->IsUpdate())
		{
			ButtonGlow->Off();
		}
	}
	else
	{
		if (!ButtonGlow->IsUpdate())
		{
			ButtonGlow->On();
		}
	}
}
