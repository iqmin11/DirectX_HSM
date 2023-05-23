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
	TowerAreaRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	TowerAreaRenderer->SetTexture("terrain_0004.png");
	TowerAreaRenderer->GetTransform()->SetWorldScale({128,128,1});
	TowerAreaRenderer->GetTransform()->SetLocalPosition({ 0,0,1 });
	TowerRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
}



