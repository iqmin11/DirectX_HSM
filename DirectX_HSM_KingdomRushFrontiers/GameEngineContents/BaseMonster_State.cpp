#include "PrecompileHeader.h"
#include "BaseMonster.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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

				if (true)
				{

				}

				if (State == MonsterState::Attack)
				{
					MonsterFSM.ChangeState("Attack");
				}

				if (State == MonsterState::Death)
				{
				}

				if (State == MonsterState::Move)
				{
					MonsterFSM.ChangeState("Move");
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
				std::string PrevDirStr = DirString;
				WalkPath(_DeltaTime);
				CalMonsterDir();
				if (PrevDirStr != DirString)
				{
					MonsterRenderer->ChangeAnimation("Move" + DirString);
					PrevDirStr = DirString;
				}

				if (CurHP <= 0)
				{
					State = MonsterState::Death;
				}

				if (State == MonsterState::Attack)
				{
					MonsterFSM.ChangeState("Attack");
				}

				if (State == MonsterState::Death)
				{
					MonsterFSM.ChangeState("Death");
				}

				if (State == MonsterState::Idle)
				{
					MonsterFSM.ChangeState("Idle");
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
				MonsterRenderer->ChangeAnimation("Attack");
			},
			.Update = [this](float _DeltaTime)
			{

				if (CurHP <= 0)
				{
					State = MonsterState::Death;
				}

				if (State == MonsterState::Idle)
				{
					MonsterFSM.ChangeState("Idle");
				}

				if (State == MonsterState::Death)
				{
					MonsterFSM.ChangeState("Death");
				}

				if (State == MonsterState::Move)
				{
					MonsterFSM.ChangeState("Move");
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
				MonsterRenderer->ChangeAnimation("Death");
				LifeBar->Off();
				LifeBarBg->Off();
				MonsterCol->Off();
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
				}
			},
			.End = [this]()
			{

			},
		});
}