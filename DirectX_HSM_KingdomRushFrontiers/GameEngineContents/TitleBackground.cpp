#include "PrecompileHeader.h"
#include "TitleBackground.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

TitleBackground::TitleBackground()
{

}

TitleBackground::~TitleBackground()
{

}

void TitleBackground::Start()
{
	BackgroundRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BackgroundRenderer->SetPipeLine("2DTexture");
	BackgroundRenderer->SetTexture("mainmenu_bg.png");
	BackgroundRenderer->GetTransform()->SetWorldScale(RenderScale);
}


void TitleBackground::Update(float _DeltaTime)
{
	
}
