#include "PrecompileHeader.h"
#include "DessertArcher.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseFighter.h"
#include "DessertArcher_Bullet.h"

DessertArcher::DessertArcher()
{

}

DessertArcher::~DessertArcher()
{

}

float4 DessertArcher::GetRangeTargetPos()
{
	return RangeTargetFighter->GetTransform()->GetWorldPosition();
}

void DessertArcher::Start()
{
	BaseMonster::Start();
	Data.SetData(MonsterEnum::DessertArcher);
	MonsterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "DessertArcher_Idle", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Back", .SpriteName = "DessertArcher_Move_Back", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Front", .SpriteName = "DessertArcher_Move_Front", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Profile", .SpriteName = "DessertArcher_Move_Profile", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "DessertArcher_Attack", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "RangedAttack", .SpriteName = "DessertArcher_RangedAttack", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "DessertArcher_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death_Explosion", .SpriteName = "Small_Explosion", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	MonsterCol->GetTransform()->SetLocalPosition(ColLocalPos);

	RangeCol = CreateComponent<GameEngineCollision>(ColOrder::MonsterRange);
	RangeCol->GetTransform()->SetWorldScale({ Range*2, Range*2 });
	CurHP = Data.Hp;

	MonsterRenderer->SetAnimationStartEvent("Attack", 3, std::bind(&DessertArcher::Attack, this));
	MonsterRenderer->SetAnimationStartEvent("RangedAttack", 3, [this]()
		{
			DessertArcher_Bullet::ShootingBullet(GetLevel(), this);
		});

	IdleStateInit();
	MoveStateInit();
	AttackStateInit();
	DeathStateInit();
	RangeAttackStateInit();

	MonsterFSM.ChangeState("Move");
}

void DessertArcher::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);

}

std::shared_ptr<class BaseFighter> DessertArcher::FindRangeTargetFighter()
{
	if (RangeCol->Collision(ColOrder::Fighter, ColType::SPHERE2D, ColType::SPHERE2D) == nullptr)
	{
		return nullptr;
	}
	else
	{
		return RangeCol->Collision(ColOrder::Fighter, ColType::SPHERE2D, ColType::SPHERE2D)->GetActor()->DynamicThis<BaseFighter>();
	}
}

void DessertArcher::CalTargetPos()
{
	RangeTargetPos = RangeTargetFighter->GetFighterCol()->GetTransform()->GetWorldPosition();
}


