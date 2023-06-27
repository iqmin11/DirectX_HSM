#include "PrecompileHeader.h"
#include "PriceTag.h"

#include <GameEngineCore\GameEngineUIRenderer.h>
#include "UIFontRenderer.h"

const float4 PriceTag::ValidFontColor = float4{ 216.f, 188.f, 4.f } / 255.f;
const float4 PriceTag::InvalidFontColor = float4{ .5f, .5f, .5f};

PriceTag::PriceTag()
{

}

PriceTag::~PriceTag()
{

}

void PriceTag::SetPrice(int _Price)
{
	PriceRender->SetText(std::to_string(_Price));
}

void PriceTag::SetColor(float4 _RGBA)
{
	PriceRender->SetColor(_RGBA);
}

void PriceTag::Start()
{
	PriceTagBg = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_0);
	PriceTagBg->SetTexture("price_tag.png");
	PriceTagBg->GetTransform()->SetWorldScale(BgScale);

	PriceRender = CreateComponent<UIFontRenderer>(UIRenderOrder::StageUI_0);
	PriceRender->SetFont("³ª´®¼Õ±Û¾¾ Ææ OTF");
	PriceRender->SetScale(FontScale);
	PriceRender->SetFontFlag(FW1_CENTER);
	float4 RGBA = float4{ 216.f, 188.f, 4.f} / 255.f;
	PriceRender->SetColor(RGBA);
	PriceRender->GetTransform()->SetLocalPosition(FontLocPos);
}

void PriceTag::Update(float _DeltaTime)
{
}
