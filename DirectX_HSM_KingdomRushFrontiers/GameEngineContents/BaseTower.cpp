#include "PrecompileHeader.h"
#include "BaseTower.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

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

	RangeCol = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::TowerRange));
}

void BaseTower::Update(float _DeltaTime)
{
	//타겟 위치를 계산하는 함수 필요
}

//std::shared_ptr<class BaseMonster> BaseTower::FindTargetMonster()
//{
//}

bool BaseTower::IsThereTarget()
{
	if (nullptr != RangeCol->Collision(ColOrder::Monster, ColType::SPHERE2D, ColType::AABBBOX2D))
	{
		return true;
	}
	return false;
}




