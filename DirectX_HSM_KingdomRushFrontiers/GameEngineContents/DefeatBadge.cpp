#include "PrecompileHeader.h"
#include "DefeatBadge.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

DefeatBadge::DefeatBadge()
{

}

DefeatBadge::~DefeatBadge()
{

}

void DefeatBadge::Start()
{
	BadgeRenderer = CreateComponent<GameEngineUIRenderer>();
	BadgeRenderer->SetTexture("victoryBadges_0004.png");
	BadgeRenderer->GetTransform()->SetWorldScale(RenderScale);
}

void DefeatBadge::Update(float _DeltaTime)
{

}
