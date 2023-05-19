#include "PrecompileHeader.h"
#include "Artillery_Bullet.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "Artillery_Tower.h"

Artillery_Bullet::Artillery_Bullet()
{

}

Artillery_Bullet::~Artillery_Bullet()
{

}

void Artillery_Bullet::ShootingBullet(GameEngineLevel* _Level, GameEngineActor* _ParentActor, TowerData* _Data)
{
	std::shared_ptr<Artillery_Bullet> Bullet = nullptr;
	Bullet = _Level->CreateActor<Artillery_Bullet>();
	Bullet->BulletRenderer->SetTexture("bombs_000" + std::to_string(_Data->Level) + ".png");
	Bullet->SetParentPos(_ParentActor->GetTransform()->GetWorldPosition());
	Bullet->SetTargetPos(dynamic_cast<Artillery_Tower*>(_ParentActor)->GetTargetPos());
	Bullet->CalBezierMid();
	Bullet->IsBezier = true;
	Bullet->BulletTime = _Data->BulletTime;
	if (_Data->Level == 1 || _Data->Level == 2)
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
	BulletRenderer->GetTransform()->SetWorldScale(BulletScale);
}
