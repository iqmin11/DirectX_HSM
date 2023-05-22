#include "PrecompileHeader.h"
#include "Ranged_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BaseMonster.h"
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
	BulletRenderer->GetTransform()->SetWorldScale(ArrowRenderScale);
	BulletRenderer->SetTexture("arrow.png");
	BulletCol->GetTransform()->SetWorldScale(ArrowColScale);
	BulletHit = std::bind(&Ranged_Bullet::ArrowHit, this);
	BulletMiss = std::bind(&Ranged_Bullet::ArrowMiss, this);
	MissArrowRenderer = CreateComponent<GameEngineSpriteRenderer>();
	MissArrowRenderer->SetTexture("decal_arrow.png");
	MissArrowRenderer->GetTransform()->SetWorldScale(MissArrowRenderScale);
	MissArrowRenderer->Off();
}

void Ranged_Bullet::Update(float _DeltaTime)
{
	BaseBullet::Update(_DeltaTime);
	if (AmIMiss)
	{
		MissUpdate(_DeltaTime);
	}
}

void Ranged_Bullet::ArrowHit()
{
	//BulletRenderer->ChangeAnimation("BoltDeath");
	Death();
	TargetMonster->CurHP -= CalDamage();
}

void Ranged_Bullet::ArrowMiss()
{
	BulletRenderer->Off();
	MissArrowRenderer->On();
}

int Ranged_Bullet::CalDamage()
{
	return BaseBullet::CalDamage();
}

void Ranged_Bullet::MissUpdate(float _DeltaTime)
{
	MissTime += _DeltaTime;
	if (2.f >= MissTime)
	{
		MissArrowRenderer->ColorOptionValue.MulColor.a -= _DeltaTime / 2;
	}
	else
	{
		Death();
	}
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