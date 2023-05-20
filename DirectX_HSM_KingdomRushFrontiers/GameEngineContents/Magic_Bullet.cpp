#include "PrecompileHeader.h"
#include "Magic_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseShootingTower.h"
#include "Magic_Shooter.h"

Magic_Bullet::Magic_Bullet()
{

}

Magic_Bullet::~Magic_Bullet()
{

}

void Magic_Bullet::ShootingBullet(GameEngineLevel* _Level, BaseShooter* _ParentShooter)
{
	std::shared_ptr<Magic_Bullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<Magic_Bullet>();
	Bullet->SetParentPos(_ParentShooter->GetTransform()->GetWorldPosition());
	Bullet->SetTargetPos(_ParentShooter->GetTargetPos());
	Bullet->CalBezierMid();
	Bullet->IsBezier = false;
	Bullet->BulletTime = _ParentShooter->GetParentTower()->GetData().BulletTime;
	Bullet->TargetMonster = _ParentShooter->GetParentTower()->GetTargetMonster();
	Bullet->Data = &_ParentShooter->GetParentTower()->GetData();
}

void Magic_Bullet::Start()
{
	BaseBullet::Start();
	BulletRenderer->GetTransform()->SetWorldScale(BulletScale);
	BulletRenderer->CreateAnimation({.AnimationName = "Bolt", .SpriteName = "MagicBolt_Shoot", .FrameInter = 0.15f,.Loop = false });
	BulletRenderer->CreateAnimation({.AnimationName = "BoltDeath", .SpriteName = "MagicBolt_Death", .FrameInter = 0.08f,.Loop = false });
	BulletRenderer->SetAnimationStartEvent("BoltDeath", 3, std::bind(&Magic_Bullet::Death, this));
	BulletRenderer->ChangeAnimation("Bolt");
	BulletDeath = std::bind(&Magic_Bullet::BoltDeath, this);
}

void Magic_Bullet::BoltDeath()
{
	BulletRenderer->ChangeAnimation("BoltDeath");
}
