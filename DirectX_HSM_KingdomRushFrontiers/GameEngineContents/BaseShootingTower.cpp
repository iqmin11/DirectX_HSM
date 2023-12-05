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

void BaseShootingTower::Start()
{
	BaseTower::Start();
	TowerRangeRender->SetTexture("range_circle.png");
	NextLvRangeRender->SetTexture("range_circle.png");
	IsThereTargetFuncPtr = std::bind(&BaseShootingTower::IsThereTarget,this);
	FindTargetMonsterFuncPtr = std::bind(&BaseShootingTower::FindTargetMonster, this);
}

void BaseShootingTower::Update(float _DeltaTime)
{
	BaseTower::Update(_DeltaTime);

	if (Construct == ConstructState::Complete)
	{
		if (UpgradeUI != nullptr)
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
	}

	if (IsThereTargetFuncPtr())
	{
		TargetMonster = FindTargetMonsterFuncPtr();
		CalTargetPos();
	}
	else
	{
		TargetMonster = nullptr;
	}
}

std::shared_ptr<class BaseMonster> BaseShootingTower::FindTargetMonster()
{
	std::vector<std::shared_ptr<GameEngineCollision>> LocalColVec0 = std::vector<std::shared_ptr<GameEngineCollision>>();
	std::vector<std::shared_ptr<GameEngineCollision>> LocalColVec1 = std::vector<std::shared_ptr<GameEngineCollision>>();
	LocalColVec0.reserve(30);
	RangeCol->CollisionAll(static_cast<int>(ColOrder::Monster), LocalColVec0, ColType::SPHERE2D, ColType::SPHERE2D);
	std::shared_ptr<BaseMonster> TargetMonster = std::shared_ptr<BaseMonster>();
	
	for (size_t i = 0; i < LocalColVec0.size(); i++)
	{
		if (LocalColVec0[i]->GetActor()->DynamicThis<BaseMonster>()->GetData().IsBurrow == false)
		{
			LocalColVec1.push_back(LocalColVec0[i]);
		}
	}
	TargetMonster = LocalColVec1[0]->GetActor()->DynamicThis<BaseMonster>();
	float Smallest = TargetMonster->CalDistance();
	for (size_t i = 0; i < LocalColVec1.size(); i++)
	{
		std::shared_ptr<BaseMonster> CompairMonster = LocalColVec1[i]->GetActor()->DynamicThis<BaseMonster>();
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
	if (nullptr == RangeCol->Collision(ColOrder::Monster, ColType::SPHERE2D, ColType::SPHERE2D))
	{
		return false;
	}
	else
	{
		std::vector<std::shared_ptr<GameEngineCollision>> LocalVec;
		LocalVec.reserve(30);
		RangeCol->CollisionAll(ColOrder::Monster, LocalVec, ColType::SPHERE2D, ColType::SPHERE2D);

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