#include "PrecompileHeader.h"
#include "Hero_Alric.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RallyPoint.h"
#include "BaseMonster.h"

Hero_Alric::Hero_Alric()
{

}

Hero_Alric::~Hero_Alric()
{

} 

void Hero_Alric::Start()
{
	BaseFighter::Start();
	BaseFighter::AttackTarget = std::bind(&Hero_Alric::AttackTarget, this);
	
	LifeBarScale = { 40,3,1 };
	LifeBarBgLocalPos = { 0,42,1 };
	LifeBarLocalPos = { 0, 42 };
	LifeBar->GetTransform()->SetWorldScale(LifeBarScale);
	LifeBar->GetTransform()->SetLocalPosition(LifeBarLocalPos);
	LifeBarBg->GetTransform()->SetWorldScale(LifeBarScale);
	LifeBarBg->GetTransform()->SetLocalPosition(LifeBarBgLocalPos);

	FighterRenderer->CreateAnimation({ .AnimationName = "Attack0", .SpriteName = "Hero_Alric_Attack_0", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Attack1", .SpriteName = "Hero_Alric_Attack_1", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Hero_Alric_Death", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Hero_Alric_Idle", .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Move", .SpriteName = "Hero_Alric_Move", .FrameInter = 0.04f, .Loop = true });
	FighterRenderer->CreateAnimation({ .AnimationName = "Revive", .SpriteName = "Hero_Alric_Revive", .FrameInter = 0.07f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Flurry", .SpriteName = "Hero_Alric_Skill_Flurry", .FrameInter = 0.075f, .Loop = false });
	FighterRenderer->CreateAnimation({ .AnimationName = "Summon", .SpriteName = "Hero_Alric_Skill_Summon", .FrameInter = 0.075f, .Loop = false });

	FighterRenderer->SetAnimationStartEvent("Attack0", 3, BaseFighter::AttackTarget);
	FighterRenderer->SetAnimationStartEvent("Attack1", 5, BaseFighter::AttackTarget);
	FighterRenderer->SetAnimationStartEvent("Flurry", 11, std::bind(&Hero_Alric::AttackFlurry, this));
	FighterRenderer->SetAnimationStartEvent("Revive", 15, [this]()
		{
			State = FighterState::Idle;
			FighterFSM.ChangeState("Idle");
		});
	FighterRenderer->SetAnimationStartEvent("Summon", 16, [this]()
		{
			State = FighterState::Idle;
			FighterFSM.ChangeState("Idle");
			SummonCooltime = 0.f;
		});
	FighterRenderer->GetTransform()->SetWorldScale(RanderScale);

	SummonCol = CreateComponent<GameEngineCollision>();
	SummonCol->GetTransform()->SetWorldScale({ SummonRange*2, SummonRange*2, 1});

	SandmanPivot.resize(3);
	for (size_t i = 0; i < SandmanPivot.size(); i++)
	{
		SandmanPivot[i] = CreateComponent<GameEngineComponent>();
	}
	SandmanPivot[0]->GetTransform()->SetLocalPosition({ -25, 0, 0 });
	SandmanPivot[1]->GetTransform()->SetLocalPosition({ 0, -25, -25 });
	SandmanPivot[2]->GetTransform()->SetLocalPosition({ 25, 0, 0 });

	IdleStateInit();
	MoveStateInit();
	TraceMonsterStateInit();
	AttackStateInit();
	ReturnStateInit();
	DeathStateInit();
	ReviveStateInit();
	CastingSkill1StateInit();
}

void Hero_Alric::Update(float _DeltaTime)
{
	BaseFighter::Update(_DeltaTime);

	if (TargetMonster != nullptr)
	{
		int a = 0;
	}

	if (IsThereSummonTarget())
	{
 		SummonTargetMonster = FindTargetMonster();
		CalTargetPos();
	}
	else
	{
		SummonTargetMonster = nullptr;
	}
	SummonCooltime += _DeltaTime;
	FighterFSM.Update(_DeltaTime);

	//Test
	if (GameEngineInput::IsDown("Z"))
	{
		CurHP = 0;
	}
}

void Hero_Alric::AttackTarget()
{
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->Hit = HitState::Melee;
}

void Hero_Alric::AttackFlurry()
{
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->CurHP -= CalDamage();
	TargetMonster->Hit = HitState::Melee;
}

int Hero_Alric::CalDamage()
{
	return BaseFighter::CalDamage();
}

std::shared_ptr<class BaseMonster> Hero_Alric::FindTargetMonster()
{
	std::vector<std::shared_ptr<GameEngineCollision>> LocalColVec = std::vector<std::shared_ptr<GameEngineCollision>>();
	LocalColVec.reserve(30);
	SummonCol->CollisionAll(static_cast<int>(ColOrder::Monster), LocalColVec, ColType::SPHERE2D, ColType::SPHERE2D);
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

void Hero_Alric::CalTargetPos()
{
	float4 CurPos = SummonTargetMonster->GetMonsterCol()->GetTransform()->GetWorldPosition();
	float4 Dir = SummonTargetMonster->GetMonsterDir();
	float MonsterSpeed = 0;
	SummonTargetPos = CurPos + Dir * MonsterSpeed;
}

bool Hero_Alric::IsThereSummonTarget()
{
	if (nullptr == SummonCol->Collision(ColOrder::Monster, ColType::SPHERE2D, ColType::SPHERE2D))
	{
		return false;
	}
	else
	{
		std::vector<std::shared_ptr<GameEngineCollision>> LocalVec;
		LocalVec.reserve(30);
		SummonCol->CollisionAll(ColOrder::Monster, LocalVec, ColType::SPHERE2D, ColType::SPHERE2D);

		for (size_t i = 0; i < LocalVec.size(); i++)
		{
			std::weak_ptr<BaseMonster> TempMonster(LocalVec[i]->GetActor()->DynamicThis<BaseMonster>());
			if (TempMonster.lock()->GetData().IsBurrow == false && TempMonster.lock()->GetData().IsFlying == false)
			{
				return true;
			}
		}
		return false;
	}
}
