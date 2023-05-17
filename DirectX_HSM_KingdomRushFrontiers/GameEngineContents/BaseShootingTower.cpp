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
		Time += _DeltaTime;
		if (Time >= Data.FireRate)
		{
			Time = 0;
			Attack();
		}
	}
	else
	{
		TargetMonster = nullptr;
		TargetPos = float4::Zero;
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
	float BulletSpeed = 1.0f; // ���߿� ���⸸ �����ؾ��ҵ�....

	TargetPos = CurPos + Dir * MonsterSpeed * BulletSpeed;
}

bool BaseShootingTower::IsThereTarget()
{
	if (nullptr != RangeCol->Collision(ColOrder::Monster, ColType::SPHERE2D, ColType::AABBBOX2D))
	{
		return true;
	}
	return false;
}