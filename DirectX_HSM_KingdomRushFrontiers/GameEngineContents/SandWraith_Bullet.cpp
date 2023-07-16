#include "PrecompileHeader.h"
#include "SandWraith_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BaseFighter.h"
#include "SandWraith.h"

SandWraith_Bullet::SandWraith_Bullet()
{

}

SandWraith_Bullet::~SandWraith_Bullet()
{

}

void SandWraith_Bullet::ShootingBullet(GameEngineLevel* _Level, SandWraith* _ParentActor)
{
	std::shared_ptr<SandWraith_Bullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<SandWraith_Bullet>();
	Bullet->SetParentPos(_ParentActor->GetBulletStartPivotPos());
	Bullet->SetTargetPos(_ParentActor->GetRangeTargetPos());
	Bullet->CalBezierMid();
	Bullet->IsBezier = false;
	Bullet->BulletTime = _ParentActor->GetBulletTime();
	Bullet->TargetFighter = _ParentActor->GetRangeTargetFighter();
	Bullet->Data = _ParentActor->GetData();
}

void SandWraith_Bullet::Start()
{
	BaseMonsterBullet::Start();
	BulletRenderer->GetTransform()->SetWorldScale(BoltRenderScale);
	BulletRenderer->CreateAnimation({ .AnimationName = "Bolt", .SpriteName = "SandWraith_Bolt_Shoot", .FrameInter = 0.15f,.Loop = false });
	BulletRenderer->CreateAnimation({ .AnimationName = "BoltDeath", .SpriteName = "SandWraith_Bolt_Death", .FrameInter = 0.08f,.Loop = false });
	BulletRenderer->SetAnimationStartEvent("BoltDeath", 4, std::bind(&SandWraith_Bullet::Death, this));
	BulletRenderer->ChangeAnimation("Bolt");

	BulletCol->GetTransform()->SetWorldScale(BoltColScale);
	BulletHit = std::bind(&SandWraith_Bullet::BoltHit, this);
	BulletMiss = std::bind(&SandWraith_Bullet::BoltMiss, this);
}

void SandWraith_Bullet::BoltHit()
{
	BulletRenderer->ChangeAnimation("BoltDeath");
	TargetFighter->CurHP -= CalDamage();
}

void SandWraith_Bullet::BoltMiss()
{
	if (TargetFighter != nullptr)
	{
		TargetFighter->CurHP -= CalDamage();
	}
	BulletRenderer->ChangeAnimation("BoltDeath");
}

int SandWraith_Bullet::CalDamage()
{
	return BaseMonsterBullet::CalDamage();
}

