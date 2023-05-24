#include "PrecompileHeader.h"
#include "BaseFighter.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

BaseFighter::BaseFighter()
{

}

BaseFighter::~BaseFighter()
{

}

void BaseFighter::Start()
{
	FighterRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	FighterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "ReinforceA_0_Idle", .Loop = false });
	FighterRenderer->GetTransform()->SetWorldScale(FighterRendererScale);
	FighterRenderer->ChangeAnimation("Idle");
}

void BaseFighter::Update(float _DeltaTime)
{

}
