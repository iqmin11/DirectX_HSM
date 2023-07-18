#include "PrecompileHeader.h"
#include "ArchMage_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BaseMonster.h"
#include "BaseShootingTower.h"
#include "Magic_Shooter.h"

ArchMage_Bullet::ArchMage_Bullet()
{

}

ArchMage_Bullet::~ArchMage_Bullet()
{

}

void ArchMage_Bullet::ShootingBullet(GameEngineLevel* _Level, BaseShooter* _ParentShooter)
{
	std::shared_ptr<ArchMage_Bullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<ArchMage_Bullet>();
	Bullet->SetParentPos(_ParentShooter->GetTransform()->GetWorldPosition() + float4{-5, 10, 10});
	Bullet->SetTargetPos(_ParentShooter->GetTargetPos());
	Bullet->CalBezierMid();
	Bullet->IsBezier = false;
	Bullet->BulletTime = _ParentShooter->GetParentTower()->GetData().BulletTime;
	Bullet->TargetMonster = _ParentShooter->GetParentTower()->GetTargetMonster();
	Bullet->Data = _ParentShooter->GetParentTower()->GetData();
}

void ArchMage_Bullet::Start()
{
	BaseBullet::Start();
	BulletRenderer->GetTransform()->SetWorldScale(BoltRenderScale);
	BulletRenderer->CreateAnimation({ .AnimationName = "Bolt", .SpriteName = "ArchMageBolt_Shoot", .FrameInter = 0.15f,.Loop = false });
	BulletRenderer->CreateAnimation({ .AnimationName = "BoltDeath", .SpriteName = "ArchMageBolt_Death", .FrameInter = 0.08f,.Loop = false });
	BulletRenderer->SetAnimationStartEvent("BoltDeath", 3, std::bind(&ArchMage_Bullet::Death, this));
	BulletRenderer->ChangeAnimation("Bolt");
	BulletCol->GetTransform()->SetWorldScale(BoltColScale);
	BulletHit = std::bind(&ArchMage_Bullet::BoltHit, this);
	BulletMiss = std::bind(&ArchMage_Bullet::BoltMiss, this);
}

void ArchMage_Bullet::BoltHit()
{
	BulletRenderer->ChangeAnimation("BoltDeath");
	TargetMonster->Hit = HitState::Bolt;
	TargetMonster->CurHP -= CalDamage();
}

void ArchMage_Bullet::BoltMiss()
{
	if (TargetMonster != nullptr)
	{
		TargetMonster->CurHP -= CalDamage();
	}
	BulletRenderer->ChangeAnimation("BoltDeath");
}

int ArchMage_Bullet::CalDamage()
{
	return BaseBullet::CalDamage();
}
