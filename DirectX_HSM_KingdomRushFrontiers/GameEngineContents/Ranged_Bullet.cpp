#include "PrecompileHeader.h"
#include "Ranged_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseShootingTower.h"
#include "Ranged_Shooter.h"

Ranged_Bullet::Ranged_Bullet()
{

}

Ranged_Bullet::~Ranged_Bullet()
{

}

void Ranged_Bullet::Start()
{
	BaseBullet::Start();
	BulletRenderer->GetTransform()->SetWorldScale({ 20,6 });
	BulletRenderer->SetTexture("arrow.png");
}

void Ranged_Bullet::ShootingBullet(GameEngineLevel* _Level, BaseShooter* _ParentShooter)
{
	std::shared_ptr<Ranged_Bullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<Ranged_Bullet>();
	Bullet->SetParentPos(_ParentShooter->GetTransform()->GetWorldPosition());
	Bullet->SetTargetPos(_ParentShooter->GetTargetPos());
	Bullet->CalBezierMid();
	Bullet->IsBezier = true;
	Bullet->BulletTime = _ParentShooter->GetParentTower()->GetData().BulletTime;
	Bullet->TargetMonster = _ParentShooter->GetParentTower()->GetTargetMonster();
	Bullet->Data = &_ParentShooter->GetParentTower()->GetData();
}