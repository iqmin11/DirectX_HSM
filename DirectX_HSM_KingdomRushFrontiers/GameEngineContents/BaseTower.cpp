#include "PrecompileHeader.h"
#include "BaseTower.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>


BaseTower::BaseTower()
{

}

BaseTower::~BaseTower()
{

}

void BaseTower::Start()
{
	GetTransform()->SetWorldPosition(ActorPos);
	TowerAreaRenderer = CreateComponent<GameEngineSpriteRenderer>();
	TowerAreaRenderer->SetTexture("terrain_0004.png");
	TowerAreaRenderer->GetTransform()->SetWorldScale({128,128});
	TowerRenderer = CreateComponent<GameEngineSpriteRenderer>();
}



