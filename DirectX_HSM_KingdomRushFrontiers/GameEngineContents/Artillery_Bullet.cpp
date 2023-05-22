#include "PrecompileHeader.h"
#include "Artillery_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "Artillery_Tower.h"
#include "BaseMonster.h"

Artillery_Bullet::Artillery_Bullet()
{

}

Artillery_Bullet::~Artillery_Bullet()
{

}

void Artillery_Bullet::ShootingBullet(GameEngineLevel* _Level, BaseShootingTower* _ParentTower)
{
	std::shared_ptr<Artillery_Bullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<Artillery_Bullet>();
	Bullet->BulletRenderer->SetTexture("bombs_000" + std::to_string(_ParentTower->GetData().Level) + ".png");
	Bullet->SetParentPos(_ParentTower->GetTransform()->GetWorldPosition());
	Bullet->SetTargetPos(_ParentTower->GetTargetPos());
	Bullet->CalBezierMid();
	Bullet->IsBezier = true;
	Bullet->BulletTime = _ParentTower->GetData().BulletTime;
	Bullet->TargetMonster = _ParentTower->GetTargetMonster();
	Bullet->Data = &_ParentTower->GetData();
	if (_ParentTower->GetData().Level == 1 || _ParentTower->GetData().Level == 2)
	{
		Bullet->IsRot = true;
	}
	else
	{
		Bullet->IsRot = false;
	}
}

void Artillery_Bullet::Start()
{
	BaseBullet::Start();
	BulletRenderer->GetTransform()->SetWorldScale(BulletRenderScale);
	BulletHit = std::bind(&Artillery_Bullet::BombHit, this);
	BulletMiss = std::bind(&Artillery_Bullet::BombMiss, this);
}

void Artillery_Bullet::BombHit()
{
	Death();
	TargetMonster->CurHP -= CalDamage();
}

void Artillery_Bullet::BombMiss()
{
	Death();
}

int Artillery_Bullet::CalDamage()
{
	return BaseBullet::CalDamage();
}
