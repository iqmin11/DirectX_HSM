#include "PrecompileHeader.h"
#include "TitleBackground.h"
#include <GameEngineCore/GameEngineRenderer.h>

TitleBackground::TitleBackground()
{

}

TitleBackground::~TitleBackground()
{

}

void TitleBackground::Start()
{
	BackgroundRenderer = CreateComponent<GameEngineRenderer>();
	BackgroundRenderer->SetPipeLine("2DTexture");
	BackgroundRenderer->GetShaderResHelper().SetTexture("DiffuseTex", "mainmenu_bg.png");
	BackgroundRenderer->GetTransform()->SetWorldScale(RenderScale);
}

void TitleBackground::Update(float _DeltaTime)
{
	
}
