#include "PrecompileHeader.h"
#include "Sandman_Fighter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BaseMonster.h"
#include "RallyPoint.h"

void Sandman_Fighter::BornStateInit()
{
	FighterFSM.CreateState({
		.Name = "Born",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Born");
			FighterRenderer->SetAnimationStartEvent("Born", 15, [this]()
				{
					FighterFSM.ChangeState("Idle");
				});
		},
		.Update = [this](float _DeltaTime)
		{
		},
		.End = [this]()
		{
		}
		});
}

void Sandman_Fighter::IdleStateInit()
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
				FighterFSM.ChangeState("Move_Start");
				return;
			}
			else if (State != FighterState::Attack && TargetMonster != nullptr)
			{
				State = FighterState::TraceMonster;
				FighterFSM.ChangeState("TraceMonster_Start");
				return;
			}

			Time += _DeltaTime;
			LiveTime += _DeltaTime;
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

void Sandman_Fighter::MoveStartStateInit()
{
	FighterFSM.CreateState({
		.Name = "Move_Start",
		.Start = [this]()
		{
			FighterCol->Off();
			//ParentRally->ColOff();
			FighterRenderer->ChangeAnimation("Move_Start");
			if (TargetMonster != nullptr)
			{
				if (TargetMonster->TargetFighter != nullptr && TargetMonster->TargetFighter == this)
				{
					TargetMonster->TargetFighter = nullptr;
				}
				TargetMonster = nullptr;
			}
			FighterRenderer->SetAnimationStartEvent("Move_Start", 4, [this]()
				{
					FighterFSM.ChangeState("Move");
				});
			SavePos = float4::Null;
		},
		.Update = [this](float _DeltaTime)
		{
			LiveTime += _DeltaTime;

		},
		.End = [this]()
		{

		}
		});
}

void Sandman_Fighter::MoveStateInit()
{
	FighterFSM.CreateState({
		.Name = "Move",
		.Start = [this]()
		{
			FighterCol->Off();
			//ParentRally->ColOff();
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
				FighterFSM.ChangeState("Move_End");
			}

			LiveTime += _DeltaTime;
			MoveToRally(_DeltaTime);
		},
		.End = [this]()
		{

		}
		});
}

void Sandman_Fighter::MoveEndStateInit()
{
	FighterFSM.CreateState({
		.Name = "Move_End",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Move_End");
			FighterRenderer->SetAnimationStartEvent("Move_End", 4, [this]()
				{
					FighterFSM.ChangeState("Idle");
				});
		},
		.Update = [this](float _DeltaTime)
		{
			LiveTime += _DeltaTime;

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

void Sandman_Fighter::StartTraceMonsterStateInit()
{
	FighterFSM.CreateState({
		.Name = "TraceMonster_Start",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Move_Start");
			FighterRenderer->SetAnimationStartEvent("Move_Start", 4, [this]()
				{
					FighterFSM.ChangeState("TraceMonster");
				});
		},
		.Update = [this](float _DeltaTime)
		{
			LiveTime += _DeltaTime;

		},
		.End = [this]()
		{

		}
		});
}

void Sandman_Fighter::TraceMonsterStateInit()
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
				FighterFSM.ChangeState("Move_Death");
				return;
			}
			if (PrevPos != RallyPos)
			{
				State = FighterState::Move;
				FighterFSM.ChangeState("Move_Start");
				return;
			}
			else if (TargetMonster->State == MonsterState::Death)
			{
				State = FighterState::Idle;
				TargetMonster = nullptr;
				FighterFSM.ChangeState("TraceMonster_End");
				return;
			}

			if (State == FighterState::Attack)
			{
				FighterFSM.ChangeState("TraceMonster_End");
				return;
			}

			if (IsChangeTarget)
			{
				FighterFSM.ChangeState("TraceMonster");
			}
			MoveToTarget(_DeltaTime);
			LiveTime += _DeltaTime;
		},
		.End = [this]()
		{
			Ratio = 0.f;
			Time = 0.f;
		}
		});
}

void Sandman_Fighter::EndTraceMonsterStateInit()
{
	FighterFSM.CreateState({
		.Name = "TraceMonster_End",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation("Move_End");
			FighterRenderer->SetAnimationStartEvent("Move_End", 4, [this]()
				{
					switch (State)
					{
					case FighterState::Idle:
						FighterFSM.ChangeState("Idle");
						break;
					case FighterState::Attack:
						FighterFSM.ChangeState("Attack");
						break;
					default:
						break;
					}
				});
		},
		.Update = [this](float _DeltaTime)
		{
			LiveTime += _DeltaTime;

		},
		.End = [this]()
		{

		}
		});
}

void Sandman_Fighter::AttackStateInit()
{
	FighterFSM.CreateState({
		.Name = "Attack",
		.Start = [this]()
		{
			if (AttackTime >= Data.AttackRate)
			{
				FighterRenderer->ChangeAnimation("Attack");
			}
			else
			{
				FighterRenderer->ChangeAnimation("Idle");
			}
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
				FighterFSM.ChangeState("Move_Start");
				return;
			}
			else if (IsChangeTarget == true)
			{
				State = FighterState::TraceMonster;
				FighterFSM.ChangeState("TraceMonster_Start");
				return;
			}
			else if (TargetMonster->State == MonsterState::Death)
			{
				State = FighterState::Idle;
				TargetMonster = nullptr;
				FighterFSM.ChangeState("Idle");
				return;
			}

			if (TargetMonster != nullptr && TargetMonster->TargetFighter == nullptr)
			{
				TargetMonster->TargetFighter = this;
			}

			Time += _DeltaTime;
			LiveTime += _DeltaTime;
			if (Time >= Data.AttackRate)
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

void Sandman_Fighter::DeathStateInit()
{
	FighterFSM.CreateState({
		.Name = "Death",
		.Start = [this]()
		{
			LifeBar->Off();
			LifeBarBg->Off();
			FighterCol->Off();
			FighterRenderer->ChangeAnimation("Death");
			FighterRenderer->SetAnimationStartEvent("Death", 5, [this]()
				{
					Death();
				});
		},
		.Update = [this](float _DeltaTime)
		{

		},
		.End = [this]()
		{

		}
		});
}

void Sandman_Fighter::MoveDeathStateInit()
{
	FighterFSM.CreateState({
		.Name = "Move_Death",
		.Start = [this]()
		{
			LifeBar->Off();
			LifeBarBg->Off();
			FighterCol->Off();
			FighterRenderer->ChangeAnimation("Move_Death");
			FighterRenderer->SetAnimationStartEvent("Move_Death", 4, [this]()
				{
					Death();
				});
		},
		.Update = [this](float _DeltaTime)
		{
		},
		.End = [this]()
		{

		}
		});
}