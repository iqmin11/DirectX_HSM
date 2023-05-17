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
	BaseShooterRenderer->CreateAnimation({.AnimationName = "1_Attack_Down", .SpriteName = "RangedLv1_Shooter_Attack_Down"});
	BaseShooterRenderer->CreateAnimation({.AnimationName = "1_Attack_Up", .SpriteName = "RangedLv1_Shooter_Attack_Up" });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "1_Idle_Down", .SpriteName = "RangedLv1_Shooter_Idle_Down" });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "1_Idle_Up", .SpriteName = "RangedLv1_Shooter_Idle_Up" });

	BaseShooterRenderer->CreateAnimation({.AnimationName = "2_Attack_Down", .SpriteName = "RangedLv2_Shooter_Attack_Down"});
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "2_Attack_Up", .SpriteName = "RangedLv2_Shooter_Attack_Up" });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "2_Idle_Down", .SpriteName = "RangedLv2_Shooter_Idle_Down" });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "2_Idle_Up", .SpriteName = "RangedLv2_Shooter_Idle_Up" });

	BaseShooterRenderer->CreateAnimation({.AnimationName = "3_Attack_Down", .SpriteName = "RangedLv3_Shooter_Attack_Down"});
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "3_Attack_Up", .SpriteName = "RangedLv3_Shooter_Attack_Up"});
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "3_Idle_Down", .SpriteName = "RangedLv3_Shooter_Idle_Down" });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "3_Idle_Up", .SpriteName = "RangedLv3_Shooter_Idle_Up" });

	BaseShooterRenderer->GetTransform()->SetWorldScale(RenderScalse);

	BaseShooterRenderer->ChangeAnimation("1_Idle_Down");
}

void Ranged_Shooter::ChangeShooterRenderer(TowerEnum _Tower)
{
	BaseShooterRenderer->ChangeAnimation(std::to_string(static_cast<int>(_Tower) + 1) + "_Idle_Down");
}

void Ranged_Shooter::Attack()
{
	Ranged_Bullet::ShootingBullet(GetLevel(), this);
}

//타겟 위치와 내위치의 차이로 구할 수 있는 Dir,
//타겟 몬스터가 정해졌나 안정해졌나로 알 수 있는 State,
//타워 데이터 받아오면 알 수 있는 AnimationChange가 필요.