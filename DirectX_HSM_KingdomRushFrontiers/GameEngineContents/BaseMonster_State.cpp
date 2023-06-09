#include "PrecompileHeader.h"
#include "BaseMonster.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseFighter.h"
#include "PopText.h"

void BaseMonster::IdleStateInit()
{
	MonsterFSM.CreateState(
		{
			.Name = "Idle",
			.Start = [this]()
			{
				MonsterRenderer->ChangeAnimation("Idle");
			},
			.Update = [this](float _DeltaTime)
			{
				if (CurHP <= 0)
				{
					State = MonsterState::Death;
					MonsterFSM.ChangeState("Death");
					return;
				}

				if (TargetFighter == nullptr)
				{
					State = MonsterState::Move;
					MonsterFSM.ChangeState("Move");
					return;
				}

				if (TargetFighter->State == FighterState::Death)
				{
					State = MonsterState::Move;
					TargetFighter = nullptr;
					MonsterFSM.ChangeState("Move");
					return;
				}

				AttackTime += _DeltaTime;
				if (MonsterCol->GetTransform()->Collision({._OtherTrans = TargetFighter->GetFighterCol()->GetTransform(), .ThisType = ColType::SPHERE2D, .OtherType = ColType::SPHERE2D}))
				{
					State = MonsterState::Attack;
					MonsterFSM.ChangeState("Attack");
					return;
				}

			},
			.End = [this]()
			{

			},
		});
}

void BaseMonster::MoveStateInit()
{
	MonsterFSM.CreateState(
		{
			.Name = "Move",
			.Start = [this]()
			{
				MonsterRenderer->ChangeAnimation("Move_Profile");
			},
			.Update = [this](float _DeltaTime)
			{
				if (CurHP <= 0)
				{
					State = MonsterState::Death;
					MonsterFSM.ChangeState("Death");
					return;
				}
				
				if (TargetFighter != nullptr && State != MonsterState::Attack)
				{
					State = MonsterState::Idle;
					MonsterFSM.ChangeState("Idle");
					return;
				}

				std::string PrevDirStr = DirString;
				WalkPath(_DeltaTime);
				CalMonsterDir();
				if (PrevDirStr != DirString)
				{
					MonsterRenderer->ChangeAnimation("Move" + DirString);
					PrevDirStr = DirString;
				}
			},
			.End = [this]()
			{

			},
		});
}

void BaseMonster::AttackStateInit()
{
	MonsterFSM.CreateState(
		{
			.Name = "Attack",
			.Start = [this]()
			{
				if (0.f <= GetTransform()->GetWorldPosition().x - TargetFighter->GetTransform()->GetWorldPosition().x)
				{
					MonsterRenderer->GetTransform()->SetLocalNegativeScaleX();
				}
				else
				{
					MonsterRenderer->GetTransform()->SetLocalPositiveScaleX();
				}
			},
			.Update = [this](float _DeltaTime)
			{

				if (CurHP <= 0)
				{
					State = MonsterState::Death;
				}

				if (TargetFighter == nullptr)
				{
					State = MonsterState::Move;
					MonsterFSM.ChangeState("Move");
					return;
				}

				if (TargetFighter->State == FighterState::Death)
				{
					State = MonsterState::Move;
					TargetFighter = nullptr;
					MonsterFSM.ChangeState("Move");
					return;
				}

				if (State == MonsterState::Idle)
				{
					MonsterFSM.ChangeState("Idle");
				}

				if (State == MonsterState::Death)
				{
					MonsterFSM.ChangeState("Death");
				}

				AttackTime += _DeltaTime;
				if (AttackTime >= Data.AttackRate)
				{
					if (0.f <= GetTransform()->GetWorldPosition().x - TargetFighter->GetTransform()->GetWorldPosition().x)
					{
						MonsterRenderer->GetTransform()->SetLocalNegativeScaleX();
					}
					else
					{
						MonsterRenderer->GetTransform()->SetLocalPositiveScaleX();
					}
					AttackTime = 0.f;
					MonsterRenderer->ChangeAnimation("Attack");
				}
			},
			.End = [this]()
			{

			},
		});
}

void BaseMonster::DeathStateInit()
{
	MonsterFSM.CreateState(
		{
			.Name = "Death",
			.Start = [this]()
			{
				PopText::CreatePopText(Hit,DynamicThis<GameEngineActor>());
				if (nullptr != MonsterRenderer->FindAnimation("Death_Explosion"))
				{
					if (Hit == HitState::Bomb)
					{
						MonsterRenderer->ChangeAnimation("Death_Explosion");
					}
					else
					{
						MonsterRenderer->ChangeAnimation("Death");
					}
				}
				else
				{
					MonsterRenderer->ChangeAnimation("Death");
				}

				LifeBar->Off();
				LifeBarBg->Off();
				MonsterCol->Off(); 
				GiveBounty();
			},
			.Update = [this](float _DeltaTime)
			{
				DeathTime += _DeltaTime;
				if (DeathTime <= 2.f)
				{
					MonsterRenderer->ColorOptionValue.MulColor.a -= _DeltaTime / 2;
				}
				else
				{
					Death();
					LiveMonsterListRelease();
				}
			},
			.End = [this]()
			{

			},
		});
}




