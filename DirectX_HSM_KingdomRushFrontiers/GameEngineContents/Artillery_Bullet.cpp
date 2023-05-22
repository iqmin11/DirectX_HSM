#include "PrecompileHeader.h"
#include "Artillery_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
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
	if (_ParentTower->GetData().Level != 3)
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

	BombCol0 = CreateComponent<GameEngineCollision>(ColOrder::Bullet);
	BombCol0->GetTransform()->SetWorldScale(ColScale0);
	BombCol1 = CreateComponent<GameEngineCollision>(ColOrder::Bullet);
	BombCol1->GetTransform()->SetWorldScale(ColScale1);
	BombCol2 = CreateComponent<GameEngineCollision>(ColOrder::Bullet);
	BombCol2->GetTransform()->SetWorldScale(ColScale2);
}

void Artillery_Bullet::BombHit()
{
	Boom();
	Death();
}

void Artillery_Bullet::BombMiss()
{
	Boom();
	Death();
}

void Artillery_Bullet::Boom()
{
	std::vector<std::shared_ptr<GameEngineCollision>> HitMonsters = std::vector<std::shared_ptr<GameEngineCollision>>();
	HitMonsters.reserve(30);
	BombCol0->CollisionAll(ColOrder::Monster, ColType::SPHERE2D, ColType::AABBBOX2D, HitMonsters);
	for (size_t i = 0; i < HitMonsters.size(); i++)
	{
		dynamic_cast<BaseMonster*>(HitMonsters[i]->GetActor())->CurHP -= CalDamage();
	}

	BombCol1->CollisionAll(ColOrder::Monster, ColType::SPHERE2D, ColType::AABBBOX2D, HitMonsters);
	for (size_t i = 0; i < HitMonsters.size(); i++)
	{
		dynamic_cast<BaseMonster*>(HitMonsters[i]->GetActor())->CurHP -= CalDamage();
	}

	BombCol2->CollisionAll(ColOrder::Monster, ColType::SPHERE2D, ColType::AABBBOX2D, HitMonsters);
	for (size_t i = 0; i < HitMonsters.size(); i++)
	{
		dynamic_cast<BaseMonster*>(HitMonsters[i]->GetActor())->CurHP -= CalDamage();
	}
}

int Artillery_Bullet::CalDamage()
{
	return (BaseBullet::CalDamage()) / 3;
}
