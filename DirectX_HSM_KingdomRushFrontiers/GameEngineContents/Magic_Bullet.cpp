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

void Magic_Bullet::ShootingBullet(GameEngineLevel* _Level, GameEngineActor* _ParentActor)
{
	std::shared_ptr<Magic_Bullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<Magic_Bullet>();
	Bullet->SetParentPos(_ParentActor->GetTransform()->GetWorldPosition());
	Bullet->SetTargetPos(dynamic_cast<Magic_Shooter*>(_ParentActor)->GetTargetPos());
	Bullet->CalBezierMid();
}

void Magic_Bullet::Start()
{
	BaseBullet::Start();
	BulletRenderer->GetTransform()->SetWorldScale({ 20,6 });
	BulletRenderer->SetTexture("arrow.png");
}
