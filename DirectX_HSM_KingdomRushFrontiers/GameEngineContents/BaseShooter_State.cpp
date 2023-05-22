#include "PrecompileHeader.h"
#include "Ranged_Shooter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseShootingTower.h"
#include "BaseShooter.h"
#include "Ranged_Bullet.h"

void BaseShooter::IdleStateInit()
{
	ShooterFSM.CreateState({
		.Name = "Idle",
		.Start = [this]()
		{
			if (ParentTower == nullptr)
			{
				BaseShooterRenderer->ChangeAnimation("1_Idle_Down");
				IsShootBullet = false;
				return;
			}

			std::string Label = std::string();
			Label = std::to_string(ParentTower->GetData().Level) + "_Idle_" + Dir_y;
			BaseShooterRenderer->ChangeAnimation(Label);
			if (Dir_x == "Left")
			{
				BaseShooterRenderer->GetTransform()->SetLocalNegativeScaleX();
			}
			else
			{
				BaseShooterRenderer->GetTransform()->SetLocalPositiveScaleX();
			}
			IsShootBullet = false;
		},
		.Update = [this](float _DeltaTime)
		{
			if (StateValue == ShooterState::Attack)
			{
				ShooterFSM.ChangeState("Attack");
				return;
			}
		},
		.End = [this]()
		{

		}
		});
}

void BaseShooter::AttackStateInit()
{
	ShooterFSM.CreateState({
		.Name = "Attack",
		.Start = [this]()
		{
			if (ParentTower == nullptr)
			{
				BaseShooterRenderer->ChangeAnimation("1_Attack_Down");
				IsShootBullet = false;
				return;
			}

			std::string Label = std::string();
			Label = std::to_string(ParentTower->GetData().Level) + "_Attack_" + Dir_y;
			BaseShooterRenderer->ChangeAnimation(Label);
			if (Dir_x == "Left")
			{
				BaseShooterRenderer->GetTransform()->SetLocalNegativeScaleX();
			}
			else
			{
				BaseShooterRenderer->GetTransform()->SetLocalPositiveScaleX();
			}
		},
		.Update = [this](float _DeltaTime)
		{
			if (BaseShooterRenderer->IsAnimationEnd())
			{
				StateValue = ShooterState::Idle;
			}

			if (StateValue == ShooterState::Idle)
			{
				ShooterFSM.ChangeState("Idle");

				return;
			}
			//Attack();
		},
		.End = [this]()
		{
		}
		});
}
