#include "PrecompileHeader.h"
#include "Hero_Alric.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BaseMonster.h"
#include "RallyPoint.h"
#include "Sandman_RallyPoint.h"

void Hero_Alric::IdleStateInit()
{
	FighterFSM.CreateState({
		.Name = "Idle",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Idle");
			SavePos = float4::Null;
		},
		.Update = [this](float _DeltaTime)
		{
			float4 RallyPos = RallyTransform->GetWorldPosition();
			if (CurHP <= 0)
			{
				State = FighterState::Death;
				FighterFSM.ChangeState("Death");
				return;
			}
			else if (PrevPos != RallyPos)
			{
				State = FighterState::Move;
				FighterFSM.ChangeState("Move");
				return;
			}
			else if (SummonCooltime >= 10.f && SummonTargetMonster != nullptr)
			{
				State = FighterState::Skill1;
				FighterFSM.ChangeState("Summon");
			}
			else if (State != FighterState::Attack && TargetMonster != nullptr)
			{
				State = FighterState::TraceMonster;
				FighterFSM.ChangeState("TraceMonster");
				return;
			}

			

			Time += _DeltaTime;
			if (Time >= 3)
			{
				IdleAutoHeal(_DeltaTime);
			}
		},
		.End = [this]()
		{
			Time = 0.f;
			HealTime = 0.f;
		}
		});
}

void Hero_Alric::MoveStateInit()
{
	FighterFSM.CreateState({
		.Name = "Move",
		.Start = [this]()
		{
			FighterCol->Off();
			ParentRally->ColOff();
			FighterRenderer->ChangeAnimation("Move");
			if (TargetMonster != nullptr)
			{
				if (TargetMonster->TargetFighter != nullptr && TargetMonster->TargetFighter == this)
				{
					TargetMonster->TargetFighter = nullptr;
				}
				TargetMonster = nullptr;
			}
			SavePos = float4::Null;
		},
		.Update = [this](float _DeltaTime)
		{
			if (State == FighterState::Idle)
			{
				FighterFSM.ChangeState("Idle");
			}

			MoveToRally(_DeltaTime);
		},
		.End = [this]()
		{
			FighterCol->On();
			ParentRally->ColOn();
			float4 RallyPos = RallyTransform->GetWorldPosition();
			PrevPos = RallyPos;
			Ratio = 0.f;
			Time = 0.f;
		}
		});
}

void Hero_Alric::TraceMonsterStateInit()
{
	FighterFSM.CreateState({
	.Name = "TraceMonster",
	.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Move");
			SavePos = GetTransform()->GetWorldPosition();
		},
		.Update = [this](float _DeltaTime)
		{
			float4 RallyPos = RallyTransform->GetWorldPosition();
			if (CurHP <= 0)
			{
				State = FighterState::Death;
				FighterFSM.ChangeState("Death");
				return;
			}
			if (PrevPos != RallyPos)
			{
				State = FighterState::Move;
				FighterFSM.ChangeState("Move");
				return;
			}
			else if (TargetMonster->State == MonsterState::Death)
			{
				State = FighterState::Return;
				TargetMonster = nullptr;
				FighterFSM.ChangeState("Return");
				return;
			}

			if (State == FighterState::Attack)
			{
				FighterFSM.ChangeState("Attack");
				return;
			}

			if (IsChangeTarget)
			{
				FighterFSM.ChangeState("TraceMonster");
			}
			MoveToTarget(_DeltaTime);
		},
		.End = [this]()
		{
			Ratio = 0.f;
			Time = 0.f;
		}
		});
}

void Hero_Alric::AttackStateInit()
{
	FighterFSM.CreateState({
	.Name = "Attack",
	.Start = [this]()
		{
			int RandomInt = GameEngineRandom::MainRandom.RandomInt(0,1);
			FighterRenderer->ChangeAnimation("Attack" + std::to_string(RandomInt));
		},
		.Update = [this](float _DeltaTime)
		{
			float4 RallyPos = RallyTransform->GetWorldPosition();
			if (CurHP <= 0)
			{
				State = FighterState::Death;
				FighterFSM.ChangeState("Death");
				return;
			}
			if (PrevPos != RallyPos)
			{
				State = FighterState::Move;
				FighterFSM.ChangeState("Move");
				return;
			}
			else if (IsChangeTarget == true)
			{
				State = FighterState::TraceMonster;
				FighterFSM.ChangeState("TraceMonster");
				return;
			}
			else if (TargetMonster->State == MonsterState::Death)
			{
				State = FighterState::Return;
				TargetMonster = nullptr;
				FighterFSM.ChangeState("Return");
				return;
			}

			if (TargetMonster != nullptr && TargetMonster->TargetFighter == nullptr)
			{
				TargetMonster->TargetFighter = this;
			}

			Time += _DeltaTime;
			FlurryCooltime += _DeltaTime;
			if (Time >= Data.AttackRate)
			{
				Time = 0.f;
				if (FlurryCooltime >= 6.f)
				{
					FlurryCooltime = 0.f;
					FighterRenderer->ChangeAnimation("Flurry");
				}
				else
				{
					int RandomInt = GameEngineRandom::MainRandom.RandomInt(0, 1);
					FighterRenderer->ChangeAnimation("Attack" + std::to_string(RandomInt));
				}
			}
		},
		.End = [this]()
		{
			Ratio = 0.f;
			Time = 0.f;
		}
		});
}

void Hero_Alric::ReturnStateInit()
{
	FighterFSM.CreateState({
	.Name = "Return",
	.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Move");
			SavePos = GetTransform()->GetWorldPosition();
		},
		.Update = [this](float _DeltaTime)
		{
			float4 RallyPos = RallyTransform->GetWorldPosition();
			if (CurHP <= 0)
			{
				State = FighterState::Death;
				FighterFSM.ChangeState("Death");
				return;
			}
			if (PrevPos != RallyPos)
			{
				State = FighterState::Move;
				FighterFSM.ChangeState("Move");
				return;
			}
			else if (State != FighterState::Attack && TargetMonster != nullptr)
			{
				State = FighterState::TraceMonster;
				FighterFSM.ChangeState("TraceMonster");
				return;
			}
			else if (Ratio >= 1.f)
			{
				State = FighterState::Idle;
				FighterFSM.ChangeState("Idle");
				return;
			}

			if (State == FighterState::Death)
			{
				FighterFSM.ChangeState("Death");
				return;
			}

			ReturnToRally(_DeltaTime);
		},
		.End = [this]()
		{
			Ratio = 0.f;
			Time = 0.f;
		}
		});
}

void Hero_Alric::DeathStateInit()
{
	FighterFSM.CreateState({
	.Name = "Death",
	.Start = [this]()
		{
			LifeBar->Off();
			LifeBarBg->Off();
			FighterCol->Off();
			FighterRenderer->ChangeAnimation("Death");
			if (TargetMonster != nullptr)
			{
				TargetMonster = nullptr;
			}
		},
		.Update = [this](float _DeltaTime)
		{
			//if (DeathTime <= 2.f)
			//{
			//	FighterRenderer->ColorOptionValue.MulColor.a -= _DeltaTime / 2;
			//}

			DeathTime += _DeltaTime;

			if (DeathTime >= 5.f)
			{
				State = FighterState::Revive;
				FighterFSM.ChangeState("Revive");
			}
		},
		.End = [this]()
		{
			DeathTime = 0.f;
		}
		});
}

void Hero_Alric::ReviveStateInit()
{
	FighterFSM.CreateState({
	.Name = "Revive",
	.Start = [this]()
		{
			LifeBar->On();
			LifeBarBg->On();
			FighterCol->On();
			CurHP = Data.Hp;
			FighterRenderer->SetAnimationStartEvent("Revive", 15, [this]()
				{
					State = FighterState::Idle;
					FighterFSM.ChangeState("Idle");
				});
			FighterRenderer->ChangeAnimation("Revive"); 
		},
		.Update = [this](float _DeltaTime)
		{

		},
		.End = [this]()
		{

		}
		});
}

void Hero_Alric::CastingSkill1StateInit()
{
	FighterFSM.CreateState({
	.Name = "Summon",
	.Start = [this]()
		{
			FighterRenderer->SetAnimationStartEvent("Summon", 16, [this]()
				{
					State = FighterState::Idle;
					FighterFSM.ChangeState("Idle");
					SummonCooltime = 0.f;
				});
			FighterRenderer->ChangeAnimation("Summon");
			Sandman_RallyPoint::CreateRallyPoint(this, SummonTargetPos);
		},
		.Update = [this](float _DeltaTime)
		{

		},
		.End = [this]()
		{

		}
		});
}

