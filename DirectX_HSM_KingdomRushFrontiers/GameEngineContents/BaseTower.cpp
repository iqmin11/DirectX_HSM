#include "PrecompileHeader.h"
#include "BaseTower.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

BaseTower::BaseTower()
{

}

BaseTower::~BaseTower()
{

}

void BaseTower::Start()
{
	GetTransform()->SetWorldPosition(ActorPos);
	TowerRenderer = CreateComponent<GameEngineSpriteRenderer>();
	TowerRenderer->SetTexture("archer_tower_0001.png");
	TowerRenderer->GetTransform()->SetWorldScale(RenderScale);
}

void BaseTower::Update(float _DeltaTime)
{

}


