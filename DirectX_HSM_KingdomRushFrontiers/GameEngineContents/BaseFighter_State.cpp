#include "PrecompileHeader.h"
#include "BaseFighter.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BaseMonster.h"
#include "RallyPoint.h"


void BaseFighter::IdleStateInit()
{
	FighterFSM.CreateState({
		.Name = "Idle",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Idle");
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

void BaseFighter::MoveStateInit()
{
	FighterFSM.CreateState({
		.Name = "Move",
		.Start = [this]()
		{
			FighterCol->Off();
			ParentRally->ColOff();
			FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Move");
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

void BaseFighter::TraceMonsterStateInit()
{
	FighterFSM.CreateState({
		.Name = "TraceMonster",
		.Start = [this]()
		{
			FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Move");
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

void BaseFighter::AttackStateInit()
{
	FighterFSM.CreateState({
		.Name = "Attack",
		.Start = [this]()
		{
			if (AttackTime >= Data.AttackRate)
			{
				FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Attack");
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

			AttackTime += _DeltaTime;
			if (AttackTime >= Data.AttackRate)
			{
				AttackTime = 0.f;
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
			FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Move");
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

void BaseFighter::DeathStateInit()
{
	FighterFSM.CreateState({
		.Name = "Death",
		.Start = [this]()
		{
			LifeBar->Off();
			LifeBarBg->Off();
			FighterCol->Off();
			FighterRenderer->ChangeAnimation(std::to_string(Data.Level) + "_Death");
		},
		.Update = [this](float _DeltaTime)
		{
			DeathTime += _DeltaTime;
			if (Data.FighterType == FighterEnum::Melee)
			{
				if (DeathTime <= 2.f)
				{
					FighterRenderer->ColorOptionValue.MulColor.a -= _DeltaTime / 2;
				}
				else
				{
					Death();
				}
			}
			else if (Data.FighterType == FighterEnum::Reinforce)
			{
				if (DeathTime <= 1.f)
				{
					FighterRenderer->ColorOptionValue.MulColor.a -= _DeltaTime;
					FighterRenderer->GetTransform()->SetLocalPositiveScaleX();
					FighterRenderer->GetTransform()->AddLocalPosition({_DeltaTime * 25, 0} );
				}
				else
				{
					Death();
				}
			}
		},
		.End = [this]()
		{

		}
		});
}