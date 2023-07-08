#include "PrecompileHeader.h"
#include "TitleBackground.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

TitleBackground::TitleBackground()
{

}

TitleBackground::~TitleBackground()
{

}

void TitleBackground::Start()
{
	BackgroundRenderer = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::Bg);
	BackgroundRenderer->SetTexture("TitleBg.png");
	BackgroundRenderer->GetTransform()->SetWorldScale(RenderScale);
}


void TitleBackground::Update(float _DeltaTime)
{
	
}
