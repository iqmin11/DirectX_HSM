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
	Bullet->Data = _ParentTower->GetData();
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

	ExplosionSmokeRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	ExplosionSmokeRender->GetTransform()->SetWorldScale(ExplosionSmokeRenderScale);
	ExplosionSmokeRender->CreateAnimation({ .AnimationName = "Boom", .SpriteName = "ArtilleryTower_ExplosionSmoke", .FrameInter = 0.05f, .Loop = false });
	ExplosionSmokeRender->ChangeAnimation("Boom");
	ExplosionSmokeRender->Off();

	BombDecalRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	BombDecalRender->SetTexture("decal_bomb_crater.png");
	BombDecalRender->GetTransform()->SetWorldScale(BombDecalRenderScale);
	BombDecalRender->GetTransform()->SetLocalPosition(BombDecalLocalPos);
	BombDecalRender->Off();
}

void Artillery_Bullet::Update(float _DeltaTime)
{
	BaseBullet::Update(_DeltaTime);
	if (IsBoom)
	{
		BombDecalRender->GetTransform()->SetWorldRotation({ 0,0,0,1 });
		ExplosionSmokeRender->GetTransform()->SetWorldRotation({0,0,0,1});
		BoomUpdate(_DeltaTime);
	}
	//ExplosionSmokeRender->On();
	//ExplosionSmokeRender->ChangeAnimation("Boom");
}

void Artillery_Bullet::BombHit()
{
	Boom();
}

void Artillery_Bullet::BombMiss()
{
	Boom();
}

void Artillery_Bullet::Boom()
{
	std::vector<std::shared_ptr<GameEngineCollision>> HitMonsters = std::vector<std::shared_ptr<GameEngineCollision>>();
	HitMonsters.reserve(30);
	BombCol0->CollisionAll(ColOrder::Monster, HitMonsters, ColType::SPHERE2D, ColType::SPHERE2D);
	for (size_t i = 0; i < HitMonsters.size(); i++)
	{
		dynamic_cast<BaseMonster*>(HitMonsters[i]->GetActor())->CurHP -= CalDamage();
	}

	BombCol1->CollisionAll(ColOrder::Monster, HitMonsters, ColType::SPHERE2D, ColType::SPHERE2D);
	for (size_t i = 0; i < HitMonsters.size(); i++)
	{
		dynamic_cast<BaseMonster*>(HitMonsters[i]->GetActor())->CurHP -= CalDamage();
	}

	BombCol2->CollisionAll(ColOrder::Monster, HitMonsters, ColType::SPHERE2D, ColType::SPHERE2D);
	for (size_t i = 0; i < HitMonsters.size(); i++)
	{
		dynamic_cast<BaseMonster*>(HitMonsters[i]->GetActor())->CurHP -= CalDamage();
	}
	IsBoom = true;
	ExplosionSmokeRender->On();
	ExplosionSmokeRender->ChangeAnimation("Boom");
	BombDecalRender->On();
	BulletRenderer->Off();
}

void Artillery_Bullet::BoomUpdate(float _DeltaTime)
{
	BoomTime += _DeltaTime;
	if (2.f >= BoomTime)
	{
		BombDecalRender->ColorOptionValue.MulColor.a -= _DeltaTime / 2;
	}
	else
	{
		Death();
	}
}

int Artillery_Bullet::CalDamage()
{
	return (BaseBullet::CalDamage()) / 3;
}
