#include "PrecompileHeader.h"
#include "Magic_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "Magic_Shooter.h"

Magic_Bullet::Magic_Bullet()
{

}

Magic_Bullet::~Magic_Bullet()
{

}

void Magic_Bullet::ShootingBullet(GameEngineLevel* _Level, GameEngineActor* _ParentActor, TowerData* _Data)
{
	std::shared_ptr<Magic_Bullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<Magic_Bullet>();
	Bullet->SetParentPos(_ParentActor->GetTransform()->GetWorldPosition());
	Bullet->SetTargetPos(dynamic_cast<Magic_Shooter*>(_ParentActor)->GetTargetPos());
	Bullet->CalBezierMid();
	Bullet->IsBezier = false;
	Bullet->BulletTime = _Data->BulletTime;
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
