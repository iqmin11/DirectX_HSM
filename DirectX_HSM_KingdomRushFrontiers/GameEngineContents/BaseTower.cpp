#include "PrecompileHeader.h"
#include "BaseTower.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "BaseShooter.h"
#include "BaseMonster.h"

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

	TowerRangeRender = CreateComponent<GameEngineSpriteRenderer>();
	TowerRangeRender->SetTexture("range_circle.png");
	//AccMonsterListPtr = &BaseMonster::AccMonsterList;
}

void BaseTower::Update(float _DeltaTime)
{
	//타겟 위치를 계산하는 함수 필요
}

//void BaseTower::FindTargetMonster()
//{
//}




