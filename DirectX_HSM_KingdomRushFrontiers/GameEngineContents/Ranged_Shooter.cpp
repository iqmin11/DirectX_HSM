#include "PrecompileHeader.h"
#include "Ranged_Shooter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseShooter.h"
#include "Ranged_Bullet.h"


Ranged_Shooter::Ranged_Shooter()
{

}

Ranged_Shooter::~Ranged_Shooter()
{

}

void Ranged_Shooter::Start()
{
	BaseShooter::Start();
	BaseShooter::Attack = std::bind(&Ranged_Shooter::Attack, this, std::placeholders::_1);
	//BaseShooter::IdleStateInit = std::bind(&Ranged_Shooter::IdleStateInit, this);
	//BaseShooter::AttackStateInit = std::bind(&Ranged_Shooter::AttackStateInit, this);
	//BaseShooter::IdleStateInit();
	//BaseShooter::AttackStateInit();

	BaseShooterRenderer->CreateAnimation({.AnimationName = "1_Attack_Down", .SpriteName = "RangedLv1_Shooter_Attack_Down",.Loop = false});
	BaseShooterRenderer->CreateAnimation({.AnimationName = "1_Attack_Up", .SpriteName = "RangedLv1_Shooter_Attack_Up",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "1_Idle_Down", .SpriteName = "RangedLv1_Shooter_Idle_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "1_Idle_Up", .SpriteName = "RangedLv1_Shooter_Idle_Up",.Loop = false });

	BaseShooterRenderer->CreateAnimation({ .AnimationName = "2_Attack_Down", .SpriteName = "RangedLv2_Shooter_Attack_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "2_Attack_Up", .SpriteName = "RangedLv2_Shooter_Attack_Up",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "2_Idle_Down", .SpriteName = "RangedLv2_Shooter_Idle_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "2_Idle_Up", .SpriteName = "RangedLv2_Shooter_Idle_Up",.Loop = false });

	BaseShooterRenderer->CreateAnimation({ .AnimationName = "3_Attack_Down", .SpriteName = "RangedLv3_Shooter_Attack_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "3_Attack_Up", .SpriteName = "RangedLv3_Shooter_Attack_Up",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "3_Idle_Down", .SpriteName = "RangedLv3_Shooter_Idle_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "3_Idle_Up", .SpriteName = "RangedLv3_Shooter_Idle_Up",.Loop = false });

	BaseShooterRenderer->GetTransform()->SetWorldScale(RenderScalse);

	BaseShooterRenderer->ChangeAnimation("1_Idle_Down");

	ShooterFSM.ChangeState("Idle");
}

//void Ranged_Shooter::Update(float _DeltaTime)
//{
//	BaseShooter::Update(_DeltaTime);
//	ShooterFSM.Update(_DeltaTime);
//}

void Ranged_Shooter::ChangeShooterRenderer(TowerEnum _Tower)
{
	BaseShooterRenderer->ChangeAnimation(std::to_string(static_cast<int>(_Tower) + 1) + "_Idle_Down");
}

void Ranged_Shooter::Attack(float _DeltaTime)
{
	if (!IsShootBullet)
	{
		Ranged_Bullet::ShootingBullet(GetLevel(), this);
		IsShootBullet = true;
	}
}

