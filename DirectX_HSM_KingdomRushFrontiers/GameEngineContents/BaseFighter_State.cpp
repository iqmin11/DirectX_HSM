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
			if (ParentRally == nullptr)
			{
				FighterRenderer->ChangeAnimation("1_Idle");
				return;
			}
			FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Idle");
			SavePos = float4::Null;
		},
		.Update = [this](float _DeltaTime)
		{
			float4 RallyPos = RallyTransform->GetWorldPosition();
			if (false/*Hp°¡ 0ÀÌ¸é*/)
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
			else if (State != FighterState::Attack && TargetMonster != nullptr)
			{
				State = FighterState::TraceMonster;
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
			if (ParentRally == nullptr)
			{
				FighterRenderer->ChangeAnimation("1_Move");
				return;
			}
			FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Move");
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
			float4 RallyPos = RallyTransform->GetWorldPosition();
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
			if (ParentRally == nullptr)
			{
				FighterRenderer->ChangeAnimation("1_Move");
				return;
			}
			FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Move");
			SavePos = GetTransform()->GetWorldPosition();
		},
		.Update = [this](float _DeltaTime)
		{
			float4 RallyPos = RallyTransform->GetWorldPosition();
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
			if (ParentRally == nullptr)
			{
				FighterRenderer->ChangeAnimation("1_Attack");
				return;
			}
			FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Attack");
		},
		.Update = [this](float _DeltaTime)
		{
			float4 RallyPos = RallyTransform->GetWorldPosition();
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

			if (State == FighterState::Death)
			{
				FighterFSM.ChangeState("Death");
				return;
			}

			Time += _DeltaTime;
			if (Time >= Data.AttackRate)
			{
				Time = 0.f;
				FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Attack");
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
			if (ParentRally == nullptr)
			{
				FighterRenderer->ChangeAnimation("1_Move");
				return;
			}
			FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Move");
			SavePos = GetTransform()->GetWorldPosition();
		},
		.Update = [this](float _DeltaTime)
		{
			float4 RallyPos = RallyTransform->GetWorldPosition();
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

void BaseFighter::DeathStateInit()
{
	FighterFSM.CreateState({
		.Name = "Death",
		.Start = [this]()
		{
			if (ParentRally == nullptr)
			{
				FighterRenderer->ChangeAnimation("1_Death");
				return;
			}
			FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Death");
		},
		.Update = [this](float _DeltaTime)
		{


		},
		.End = [this]()
		{

		}
		});
}