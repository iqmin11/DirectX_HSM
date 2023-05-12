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
	Bg->SetTexture("Bg.png");
	Bg->GetTransform()->SetWorldScale(BgScale * ScaleRatio);
}

void Background::Update(float _DeltaTime)
{
}
