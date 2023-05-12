#include "PrecompileHeader.h"
#include "BaseShooter.h"

#include<GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseBullet.h"
#include "PlayStageLevel.h"

BaseShooter::BaseShooter()
{

}

BaseShooter::~BaseShooter()
{

}

void BaseShooter::Start()
{
	BaseShooterRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BaseShooterRenderer->SetTexture("RangedTower_Level1_NPC0000.png");
	BaseShooterRenderer->GetTransform()->SetWorldScale(RenderScalse);
}

void BaseShooter::Update(float _DeltaTime)
{
	Time += _DeltaTime;
	if (Time >= AttackSpeed)
	{
		Time = 0;
		Attack();
	}
}

void BaseShooter::Attack()
{
	BaseBullet::ShootingBullet(GetLevel(), this, TestTargetPos);
}
