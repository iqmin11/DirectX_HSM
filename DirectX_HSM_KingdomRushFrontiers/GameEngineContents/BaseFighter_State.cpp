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
			SavePos = float4::Null;
		},
		.Update = [this](float _DeltaTime)
		{
			if (false/*Hp°¡ 0ÀÌ¸é*/)
			{
				State = FighterState::Death;
			}
			else if (PrevPos != RallyPos)
			{
				State = FighterState::Move;
			}			
			else if (State != FighterState::Attack && TargetMonster != nullptr)
			{
				State = FighterState::TraceMonster;
			}
			
			if (State == FighterState::Death)
			{
				FighterFSM.ChangeState("Death");
				return;
			}
			else if (State == FighterState::Move)
			{
				FighterFSM.ChangeState("Move");
				return;
			}
			else if (State == FighterState::TraceMonster)
			{
				FighterFSM.ChangeState("TraceMonster");
				return;
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
			PrevPos = RallyPos;
			Ratio = 0.f;
			Time = 0.f;
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
			SavePos = GetTransform()->GetWorldPosition();
		},
		.Update = [this](float _DeltaTime)
		{
			if (PrevPos != RallyPos)
			{
				State = FighterState::Move;
			}
			else if (TargetMonster->State == MonsterState::Death)
			{
				State = FighterState::Return;
				TargetMonster = nullptr;
			}

			if (State == FighterState::Move)
			{
				FighterFSM.ChangeState("Move");
				return;
			}

			if (State == FighterState::Return)
			{
				FighterFSM.ChangeState("Return");
				return;
			}

			if (State == FighterState::Attack)
			{
				FighterFSM.ChangeState("Attack");
				return;
			}

			if (State == FighterState::Death)
			{
				FighterFSM.ChangeState("Death");
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
			else if (IsChangeTarget == true)
			{
				State = FighterState::TraceMonster;
			}
			else if (TargetMonster->State == MonsterState::Death)
			{
				State = FighterState::Return;
				TargetMonster = nullptr;
			}

			if (State == FighterState::Move)
			{
				FighterFSM.ChangeState("Move");
				return;
			}

			if (State == FighterState::TraceMonster)
			{
				FighterFSM.ChangeState("TraceMonster");
				return;
			}

			if (State == FighterState::Return)
			{
				FighterFSM.ChangeState("Return");
				return;
			}

			if (State == FighterState::Death)
			{
				FighterFSM.ChangeState("Death");
				return;
			}

			Time += _DeltaTime;
			if (Time >= AttackRate)
			{
				Time = 0.f;
				FighterRenderer->ChangeAnimation("Attack");
			}
		},
		.End = [this]()
		{
			Ratio = 0.f;
			Time = 0.f;
		}
		});
}

void BaseFighter::ReturnStateInit()
{
	FighterFSM.CreateState({
		.Name = "Return",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Move");
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
			else if (Ratio >= 1.f)
			{
				State = FighterState::Idle;
			}

			if (State == FighterState::Move)
			{
				FighterFSM.ChangeState("Move");
				return;
			}

			if (State == FighterState::TraceMonster)
			{
				FighterFSM.ChangeState("TraceMonster");
				return;
			}

			if (State == FighterState::Idle)
			{
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


		},
		.End = [this]()
		{

		}
		});
}