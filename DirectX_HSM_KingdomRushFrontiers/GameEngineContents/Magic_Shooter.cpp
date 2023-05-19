#include "PrecompileHeader.h"
#include "Magic_Shooter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseShooter.h"
#include "Magic_Bullet.h"


Magic_Shooter::Magic_Shooter()
{

}

Magic_Shooter::~Magic_Shooter()
{

}

void Magic_Shooter::Start()
{
	BaseShooter::Start();
	BaseShooter::Attack = std::bind(&Magic_Shooter::Attack, this);
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "1_Attack_Down", .SpriteName = "Magic_Shooter_Attack_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "1_Attack_Up", .SpriteName = "Magic_Shooter_Attack_Up",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "1_Idle_Down", .SpriteName = "Magic_Shooter_Idle_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "1_Idle_Up", .SpriteName = "Magic_Shooter_Idle_Up",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "2_Attack_Down", .SpriteName = "Magic_Shooter_Attack_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "2_Attack_Up", .SpriteName = "Magic_Shooter_Attack_Up",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "2_Idle_Down", .SpriteName = "Magic_Shooter_Idle_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "2_Idle_Up", .SpriteName = "Magic_Shooter_Idle_Up",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "3_Attack_Down", .SpriteName = "Magic_Shooter_Attack_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "3_Attack_Up", .SpriteName = "Magic_Shooter_Attack_Up",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "3_Idle_Down", .SpriteName = "Magic_Shooter_Idle_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "3_Idle_Up", .SpriteName = "Magic_Shooter_Idle_Up",.Loop = false });

	BaseShooterRenderer->SetAnimationStartEvent("1_Attack_Down", 4, std::bind(&Magic_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("1_Attack_Up", 4, std::bind(&Magic_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("2_Attack_Down", 4, std::bind(&Magic_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("2_Attack_Up", 4, std::bind(&Magic_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("3_Attack_Down", 4, std::bind(&Magic_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("3_Attack_Up", 4, std::bind(&Magic_Shooter::Attack, this));

	BaseShooterRenderer->GetTransform()->SetWorldScale(RenderScalse);

	BaseShooter::IdleStateInit();
	BaseShooter::AttackStateInit();
	ShooterFSM.ChangeState("Idle");
}

void Magic_Shooter::ChangeShooterRenderer(int _TowerLevel)
{
	BaseShooterRenderer->ChangeAnimation(std::to_string(_TowerLevel) + "_Idle_Down");
}

void Magic_Shooter::Attack()
{
	if (!IsShootBullet)
	{
		Magic_Bullet::ShootingBullet(GetLevel(), this, Data);
		IsShootBullet = true;
	}
}