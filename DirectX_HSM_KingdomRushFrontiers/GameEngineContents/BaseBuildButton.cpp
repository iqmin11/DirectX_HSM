#include "PrecompileHeader.h"
#include "BaseBuildButton.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "PriceTag.h"

BaseBuildButton::BaseBuildButton()
{

}

BaseBuildButton::~BaseBuildButton()
{

}

void BaseBuildButton::SetPrice(int _Price)
{
	Price = _Price;
	AcPriceTag->SetPrice(Price);
}

void BaseBuildButton::SetInvalid()
{
	Render->SetTexture(InvalidTextureName);
	AcPriceTag->SetColor(PriceTag::InvalidFontColor);
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

	AcPriceTag = GetLevel()->CreateActor<PriceTag>();
	AcPriceTag->GetTransform()->SetWorldPosition((GetTransform()->GetWorldPosition()) + float4{0,-30});
	AcPriceTag->GetTransform()->SetParent(GetTransform());
}

void BaseBuildButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
	if (!PlayManager::MainPlayer->DoIHaveEnoughGold(Price) && InvalidTextureName != "")
	{
		SetInvalid();
	}
	else
	{
		AcPriceTag->SetColor(PriceTag::ValidFontColor);
	}

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
