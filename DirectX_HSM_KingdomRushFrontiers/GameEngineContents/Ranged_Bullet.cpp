#include "PrecompileHeader.h"
#include "Ranged_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
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

void Ranged_Bullet::ShootingBullet(GameEngineLevel* _Level, GameEngineActor* _ParentActor, TowerData* _Data)
{
	std::shared_ptr<Ranged_Bullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<Ranged_Bullet>();
	Bullet->SetParentPos(_ParentActor->GetTransform()->GetWorldPosition());
	Bullet->SetTargetPos(dynamic_cast<Ranged_Shooter*>(_ParentActor)->GetTargetPos());
	Bullet->CalBezierMid();
	Bullet->IsBezier = true;
	Bullet->BulletTime = _Data->BulletTime;
}