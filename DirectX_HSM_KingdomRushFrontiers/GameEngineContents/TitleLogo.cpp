#include "PrecompileHeader.h"
#include "TitleLogo.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

TitleLogo::TitleLogo()
{

}

TitleLogo::~TitleLogo()
{

}

void TitleLogo::Start()
{
	StartButtonRenderer = CreateComponent<GameEngineSpriteRenderer>();
	StartButtonRenderer->SetPipeLine("2DTexture");
	StartButtonRenderer->SetTexture("menu_startchain_0001.png");
	StartButtonRenderer->GetTransform()->SetWorldScale(StartButtonRenderScale * ScaleRatio);
	StartButtonRenderer->GetTransform()->SetWorldPosition(StartButtonRenderPos);

	LogoRenderer = CreateComponent<GameEngineSpriteRenderer>();
	LogoRenderer->SetPipeLine("2DTexture");
	LogoRenderer->SetTexture("logo.png");
	LogoRenderer->GetTransform()->SetWorldScale(LogoRenderScale * ScaleRatio);
	LogoRenderer->GetTransform()->SetWorldPosition(ActorPos);
}

void TitleLogo::Update(float _DeltaTime)
{
	
}
