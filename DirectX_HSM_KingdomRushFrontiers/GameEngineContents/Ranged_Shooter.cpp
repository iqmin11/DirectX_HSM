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
	BaseShooterRenderer->SetTexture("RangedTower_Level1_NPC0000.png");
	BaseShooterRenderer->GetTransform()->SetWorldScale(RenderScalse);
}

void Ranged_Shooter::ChangeShooterRenderer(TowerEnum _Tower)
{
	BaseShooterRenderer->SetTexture("RangedTower_Level" + std::to_string(static_cast<int>(_Tower) + 1) + "_NPC0000.png");
}

void Ranged_Shooter::Attack()
{
	Ranged_Bullet::ShootingBullet(GetLevel(), this);
}
