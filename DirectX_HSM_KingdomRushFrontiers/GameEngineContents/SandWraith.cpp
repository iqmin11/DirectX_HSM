#include "PrecompileHeader.h"
#include "SandWraith.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseFighter.h"
#include "SandWraith_Bullet.h"
#include "SandWraith_Coffin.h"

SandWraith::SandWraith()
{

}

SandWraith::~SandWraith()
{

}

float4 SandWraith::GetRangeTargetPos()
{
	return RangeTargetFighter.lock()->GetTransform()->GetWorldPosition();
}

float4 SandWraith::GetBulletStartPivotPos()
{
	return BulletStartPivot->GetTransform()->GetWorldPosition();
}

void SandWraith::Start()
{
	BaseMonster::Start();
	Data.SetData(MonsterEnum::SandWraith);
	BulletStartPivot = CreateComponent<GameEngineComponent>();
	BulletStartPivot->GetTransform()->SetLocalPosition(BoltStartPos);
	MonsterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "SandWraith_Idle", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Back", .SpriteName = "SandWraith_Move_Back", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Front", .SpriteName = "SandWraith_Move_Front", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Move_Profile", .SpriteName = "SandWraith_Move_Profile", .FrameInter = 0.06f, .Loop = true });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "SandWraith_Attack", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "RangedAttack", .SpriteName = "SandWraith_RangedAttack", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death", .SpriteName = "SandWraith_Death", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Death_Explosion", .SpriteName = "Small_Explosion", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->CreateAnimation({ .AnimationName = "Summon", .SpriteName = "SandWraith_Summon", .FrameInter = 0.06f, .Loop = false });
	MonsterRenderer->GetTransform()->SetWorldScale(RenderScale);
	MonsterCol->GetTransform()->SetWorldScale(ColScale);
	MonsterCol->GetTransform()->SetLocalPosition(ColLocalPos);

	RangeCol = CreateComponent<GameEngineCollision>(ColOrder::MonsterRange);
	RangeCol->GetTransform()->SetWorldScale({ Range * 2, Range * 2 });
	CurHP = Data.Hp;

	MonsterRenderer->SetAnimationStartEvent("Attack", 3, std::bind(&SandWraith::Attack, this));
	MonsterRenderer->SetAnimationStartEvent("RangedAttack", 3, [this]()
		{
			SandWraith_Bullet::ShootingBullet(GetLevel(), this);
		});
	MonsterRenderer->SetAnimationStartEvent("Summon", 21, [this]()
		{
			State = MonsterState::Move;
			MonsterFSM.ChangeState("Move");
		});
	MonsterRenderer->SetAnimationStartEvent("Summon", 3, [this]()
		{
			SandWraith_Coffin::SummonCoffin(this);
		});

	IdleStateInit();
	MoveStateInit();
	AttackStateInit();
	DeathStateInit();
	RangeAttackStateInit();
	SummonStateInit();

	MonsterFSM.ChangeState("Move");
}

void SandWraith::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);
}

std::shared_ptr<class BaseFighter> SandWraith::FindRangeTargetFighter()
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

void SandWraith::CalTargetPos()
{
	RangeTargetPos = RangeTargetFighter.lock()->GetFighterCol()->GetTransform()->GetWorldPosition();
}


