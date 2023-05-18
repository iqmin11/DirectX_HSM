#include "PrecompileHeader.h"
#include "BaseShootingTower.h"

#include <GameEngineCore/GameEngineCollision.h>
#include "BaseShooter.h"
#include "BaseMonster.h"

BaseShootingTower::BaseShootingTower()
{

}

BaseShootingTower::~BaseShootingTower()
{

}

void BaseShootingTower::Start()
{
	BaseTower::Start();
	//TowerRangeRender = CreateComponent<GameEngineSpriteRenderer>();
	//TowerRangeRender->SetTexture("range_circle.png");
	RangeCol = CreateComponent<GameEngineCollision>(static_cast<int>(ColOrder::TowerRange));
}

void BaseShootingTower::Update(float _DeltaTime)
{

	if (IsThereTarget())
	{
		TargetMonster = FindTargetMonster();
		CalTargetPos();
	}
	else
	{
		TargetMonster = nullptr;
	}
}

std::shared_ptr<class BaseMonster> BaseShootingTower::FindTargetMonster()
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

void BaseShootingTower::CalTargetPos()
{
	float4 CurPos = TargetMonster->GetTransform()->GetWorldPosition();
	float4 Dir = TargetMonster->GetMonsterDir();
	float MonsterSpeed = TargetMonster->GetMonsterSpeed();
	float BulletTime = Data.BulletTime; // 나중에 여기만 수정해야할듯....

	TargetPos = CurPos + Dir * MonsterSpeed * BulletTime;
}

bool BaseShootingTower::IsThereTarget()
{
	if (nullptr != RangeCol->Collision(ColOrder::Monster, ColType::SPHERE2D, ColType::AABBBOX2D))
	{
		return true;
	}
	return false;
}