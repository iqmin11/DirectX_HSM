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
	BaseShooter::Attack = std::bind(&Ranged_Shooter::Attack, this);

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

	BaseShooterRenderer->SetAnimationStartEvent("1_Attack_Down", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("2_Attack_Down", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("3_Attack_Down", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("1_Attack_Up", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("2_Attack_Up", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("3_Attack_Up", 1, std::bind(&Ranged_Shooter::Attack, this));

	BaseShooterRenderer->GetTransform()->SetWorldScale(RenderScalse);

	BaseShooter::IdleStateInit();
	BaseShooter::AttackStateInit();
	ShooterFSM.ChangeState("Idle");
}

void Ranged_Shooter::ChangeShooterRenderer(int _TowerLevel)
{
	BaseShooterRenderer->ChangeAnimation(std::to_string(_TowerLevel) + "_Idle_Down");
}

void Ranged_Shooter::Attack()
{
	if (!IsShootBullet)
	{
		Ranged_Bullet::ShootingBullet(GetLevel(), this, Data);
		IsShootBullet = true;
	}
}

