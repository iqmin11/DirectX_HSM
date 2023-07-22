#include "PrecompileHeader.h"
#include "Ranged_Shooter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseShootingTower.h"
#include "BaseShooter.h"
#include "Ranged_Bullet.h"

//GameEngineSoundPlayer Ranged_Shooter::ShooterSound = GameEngineSoundPlayer();

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

	BaseShooterRenderer->CreateAnimation({ .AnimationName = "0_Attack_Down", .SpriteName = "StageArcher_Attack_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "0_Attack_Up", .SpriteName = "StageArcher_Attack_Up",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "0_Idle_Down", .SpriteName = "StageArcher_Idle_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "0_Idle_Up", .SpriteName = "StageArcher_Idle_Up",.Loop = false });

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

	BaseShooterRenderer->CreateAnimation({ .AnimationName = "4_Attack_Down", .SpriteName = "RangedLv4_Shooter_Attack_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "4_Attack_Up", .SpriteName = "RangedLv4_Shooter_Attack_Up",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "4_Idle_Down", .SpriteName = "RangedLv4_Shooter_Idle_Down",.Loop = false });
	BaseShooterRenderer->CreateAnimation({ .AnimationName = "4_Idle_Up", .SpriteName = "RangedLv4_Shooter_Idle_Up",.Loop = false });

	BaseShooterRenderer->SetAnimationStartEvent("0_Attack_Down", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("1_Attack_Down", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("2_Attack_Down", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("3_Attack_Down", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("4_Attack_Down", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("0_Attack_Up", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("1_Attack_Up", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("2_Attack_Up", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("3_Attack_Up", 1, std::bind(&Ranged_Shooter::Attack, this));
	BaseShooterRenderer->SetAnimationStartEvent("4_Attack_Up", 1, std::bind(&Ranged_Shooter::Attack, this));

	BaseShooterRenderer->GetTransform()->SetWorldScale(RenderScalse);

	BaseShooter::IdleStateInit();
	BaseShooter::AttackStateInit();
	ShooterFSM.ChangeState("Idle");

	ArrowReleaseSoundNames.resize(2);
	ArrowReleaseSoundNames[0] = "Sound_ArrowRelease2.ogg";
	ArrowReleaseSoundNames[1] = "Sound_ArrowRelease3.ogg";
}

void Ranged_Shooter::PlayShooterSound(const std::string_view& _Name)
{
	if (ShooterSound.IsValid())
	{
		bool BoolValue = false;
		ShooterSound.isPlaying(&BoolValue);
		if (BoolValue)
		{
			return;
		}
	}
	ShooterSound = GameEngineSound::Play(_Name);
	ShooterSound.SetVolume(0.2f);
}

void Ranged_Shooter::PlayArrowReleaseSound()
{
	PlayShooterSound(ArrowReleaseSoundNames[GameEngineRandom::MainRandom.RandomInt(0,1)]);
}

void Ranged_Shooter::ChangeShooterRenderer(int _TowerLevel)
{
	BaseShooterRenderer->ChangeAnimation(std::to_string(_TowerLevel) + "_Idle_Down");
}

void Ranged_Shooter::Attack()
{
	if (!IsShootBullet)
	{
		Ranged_Bullet::ShootingBullet(GetLevel(), this);
		PlayArrowReleaseSound();
		IsShootBullet = true;
	}
}

