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
	if (IsThereTarget())
	{
		TargetMonster = FindTargetMonster();
		CalTargetPos();
	}
	else
	{
		TargetMonster = nullptr;
		TargetPos = float4::Zero;
	}
}

std::shared_ptr<class BaseMonster> BaseTower::FindTargetMonster()
{
	std::vector<std::shared_ptr<GameEngineCollision>> LocalColVec = std::vector<std::shared_ptr<GameEngineCollision>>();
	LocalColVec.reserve(30);
	RangeCol->CollisionAll(static_cast<int>(ColOrder::Monster), ColType::SPHERE2D, ColType::AABBBOX2D, LocalColVec);
	std::shared_ptr<BaseMonster> TargetMonster = LocalColVec[0]->GetActor()->DynamicThis<BaseMonster>();
	float Smallest = TargetMonster->CalDistance();
	for (size_t i = 0; i < LocalColVec.size(); i++)
	{
		std::shared_ptr<BaseMonster> CompairMonster = LocalColVec[i]->GetActor()->DynamicThis<BaseMonster>();
		if (Smallest <= std::min<float>(Smallest, CompairMonster->CalDistance()))
		{
			continue;
		}
		else
		{
			TargetMonster = CompairMonster;
		}
	}
	return TargetMonster;
}

void BaseTower::CalTargetPos()
{
	float4 CurPos = TargetMonster->GetTransform()->GetWorldPosition();
	float4 Dir = TargetMonster->GetMonsterDir();
	float MonsterSpeed = TargetMonster->GetMonsterSpeed();
	float BulletSpeed = 1.0f;

	TargetPos = CurPos + Dir * MonsterSpeed * BulletSpeed;
}

bool BaseTower::IsThereTarget()
{
	if (nullptr != RangeCol->Collision(ColOrder::Monster, ColType::SPHERE2D, ColType::AABBBOX2D))
	{
		return true;
	}
	return false;
}




