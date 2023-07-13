#include "PrecompileHeader.h"
#include "BaseShootingTower.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BaseShooter.h"
#include "BaseMonster.h"
#include "UpgradeTowerUI.h"

BaseShootingTower::BaseShootingTower()
{

}

BaseShootingTower::~BaseShootingTower()
{

}

void BaseShootingTower::Start()
{
	BaseTower::Start();
	TowerRangeRender->SetTexture("range_circle.png");
	NextLvRangeRender->SetTexture("range_circle.png");
}

void BaseShootingTower::Update(float _DeltaTime)
{
	BaseTower::Update(_DeltaTime);

	if (Construct == ConstructState::Complete)
	{
		if (UpgradeUI->IsUpdate())
		{
			TowerRangeRender->On();
		}
		else
		{
			TowerRangeRender->Off();
		}
	}

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
	RangeCol->CollisionAll(static_cast<int>(ColOrder::Monster), LocalColVec, ColType::SPHERE2D, ColType::SPHERE2D);
	std::shared_ptr<BaseMonster> TargetMonster = std::shared_ptr<BaseMonster>();
	
	for (size_t i = 0; i < LocalColVec.size(); i++)
	{
		if (LocalColVec[i]->GetActor()->DynamicThis<BaseMonster>()->GetData().IsBurrow == false)
		{
			TargetMonster = LocalColVec[i]->GetActor()->DynamicThis<BaseMonster>();
			break;
		}
	}
	
	float Smallest = TargetMonster->CalDistance();
	for (size_t i = 0; i < LocalColVec.size(); i++)
	{
		std::shared_ptr<BaseMonster> CompairMonster = LocalColVec[i]->GetActor()->DynamicThis<BaseMonster>();
		if (Smallest <= std::min<float>(Smallest, CompairMonster->CalDistance()) || CompairMonster->GetData().IsBurrow)
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
	float4 CurPos = TargetMonster->GetMonsterCol()->GetTransform()->GetWorldPosition();
	float4 Dir = TargetMonster->GetMonsterDir();
	float MonsterSpeed = 0;
	if (TargetMonster->State == MonsterState::Move)
	{
		MonsterSpeed = TargetMonster->GetMonsterSpeed();
	}
	float BulletTime = Data.BulletTime;

	TargetPos = CurPos + Dir * MonsterSpeed * BulletTime;
}

bool BaseShootingTower::IsThereTarget()
{
	std::vector<std::shared_ptr<GameEngineCollision>> LocalVec;
	LocalVec.reserve(30);
	RangeCol->CollisionAll(ColOrder::Monster, LocalVec, ColType::SPHERE2D, ColType::SPHERE2D);

	if (LocalVec.size() <= 0)
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < LocalVec.size(); i++)
		{
			if (LocalVec[i]->GetActor()->DynamicThis<BaseMonster>()->GetData().IsBurrow == false)
			{
				return true;
			}
		}
		return false;
	}
}