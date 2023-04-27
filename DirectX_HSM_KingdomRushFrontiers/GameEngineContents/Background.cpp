#include "PrecompileHeader.h"
#include "Background.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Background::Background()
{

}

Background::~Background()
{

}

void Background::Start()
{
	GetTransform()->SetWorldPosition(ActorPos);
	Bg = CreateComponent<GameEngineSpriteRenderer>();
	Bg->SetPipeLine("2DTexture");
	Bg->SetTexture("Bg.png");
	Bg->GetTransform()->SetWorldScale(BgScale);
}

void Background::Update(float _DeltaTime)
{
}
