#include "PrecompileHeader.h"
#include "BaseFighter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BaseMonster.h"


void BaseFighter::IdleStateInit()
{
	FighterFSM.CreateState({
		.Name = "Idle",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Idle");
		},
		.Update = [this](float _DeltaTime)
		{
			if (PrevPos != RallyPos)
			{
				State = FighterState::Move;
			}			
			else if (State != FighterState::Attack && TargetMonster != nullptr)
			{
				State = FighterState::TraceMonster;
			}
			
			if (State == FighterState::Move)
			{
				FighterFSM.ChangeState("Move");
			}

			if (State == FighterState::TraceMonster)
			{
				FighterFSM.ChangeState("TraceMonster");
			}

			if (State == FighterState::Attack)
			{
				FighterFSM.ChangeState("Attack");
			}

			if (State == FighterState::Death)
			{
				FighterFSM.ChangeState("Death");
			}
		},
		.End = [this]()
		{

		} 
		});
}

void BaseFighter::MoveStateInit()
{
	FighterFSM.CreateState({
		.Name = "Move",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Move");
			TargetMonster = nullptr;
		},
		.Update = [this](float _DeltaTime)
		{
			Time += _DeltaTime;
			Ratio = Time * (Speed / (RallyPos - PrevPos).Size());
			ActorPos = float4::LerpClamp(PrevPos, RallyPos, Ratio);
			GetTransform()->SetWorldPosition(ActorPos);
			if (Ratio >= 1)
			{
				PrevPos = RallyPos;
				Ratio = 0.f;
				Time = 0.f;
			}

			if (ActorPos.x - RallyPos.x > 0)
			{
				FighterRenderer->GetTransform()->SetLocalNegativeScaleX();
			}
			else if(ActorPos.x - RallyPos.x < 0)
			{
				FighterRenderer->GetTransform()->SetLocalPositiveScaleX();
			}

			if (PrevPos == RallyPos)
			{
				State = FighterState::Idle;
			}

			if (State == FighterState::Idle)
			{
				FighterFSM.ChangeState("Idle");
			}

			if (State == FighterState::TraceMonster)
			{
				FighterFSM.ChangeState("TraceMonster");
			}

			if (State == FighterState::Attack)
			{
				FighterFSM.ChangeState("Attack");
			}

			if (State == FighterState::Death)
			{
				FighterFSM.ChangeState("Death");
			}
		},
		.End = [this]()
		{

		}
		});
}

void BaseFighter::TraceMonsterStateInit()
{
	FighterFSM.CreateState({
		.Name = "TraceMonster",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Move");
			TargetMonster->State = MonsterState::Idle;
		},
		.Update = [this](float _DeltaTime)
		{
			MoveToTarget(_DeltaTime);

			if (State == FighterState::Move)
			{
				FighterFSM.ChangeState("Move");
			}

			if (State == FighterState::Idle)
			{
				FighterFSM.ChangeState("Idle");
			}

			if (State == FighterState::Attack)
			{
				FighterFSM.ChangeState("Attack");
			}

			if (State == FighterState::Death)
			{
				FighterFSM.ChangeState("Death");
			}
		},
		.End = [this]()
		{

		}
		});
}

void BaseFighter::AttackStateInit()
{
	FighterFSM.CreateState({
		.Name = "Attack",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Attack");
		},
		.Update = [this](float _DeltaTime)
		{
			if (PrevPos != RallyPos)
			{
				State = FighterState::Move;
			}

			Time += _DeltaTime;
			if (Time >= AttackRate)
			{
				Time = 0.f;
				FighterRenderer->ChangeAnimation("Attack");
				if (TargetMonster->State == MonsterState::Death)
				{
					TargetMonster = nullptr;
					State = FighterState::Idle;
				}
			}

			if (State == FighterState::Move)
			{
				FighterFSM.ChangeState("Move");
			}

			if (State == FighterState::Idle)
			{
				FighterFSM.ChangeState("Idle");
			}

			if (State == FighterState::TraceMonster)
			{
				FighterFSM.ChangeState("TraceMonster");
			}

			if (State == FighterState::Death)
			{
				FighterFSM.ChangeState("Death");
			}
		},
		.End = [this]()
		{

		}
		});
}

void BaseFighter::DeathStateInit()
{
	FighterFSM.CreateState({
		.Name = "Death",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Death");
		},
		.Update = [this](float _DeltaTime)
		{
			if (State == FighterState::Move)
			{
				FighterFSM.ChangeState("Move");
			}

			if (State == FighterState::TraceMonster)
			{
				FighterFSM.ChangeState("TraceMonster");
			}

			if (State == FighterState::Attack)
			{
				FighterFSM.ChangeState("Attack");
			}

			if (State == FighterState::Idle)
			{
				FighterFSM.ChangeState("Idle");
			}
		},
		.End = [this]()
		{

		}
		});
}