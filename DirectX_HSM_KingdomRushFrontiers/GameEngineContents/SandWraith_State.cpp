#include "PrecompileHeader.h"
#include "SandWraith.h"

#include <GameEngineCore\GameEngineSpriteRenderer.h>
#include "BaseFighter.h"

void SandWraith::MoveStateInit()
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

				if (RangeTargetFighter != nullptr && TargetFighter == nullptr)
				{
					State = MonsterState::RangeAttack;
					MonsterFSM.ChangeState("RangeAttack");
					return;
				}

				if (SummonCoolTime >= SummonMaxCoolTime)
				{
					if (!Walk.GetNextPointWalkData().IsNull())
					{
						State = MonsterState::Summon;
						MonsterFSM.ChangeState("Summon");
						return;
					}
				}

				RangeTargetFighter = FindRangeTargetFighter();
				std::string PrevDirStr = Walk.DirString;
				WalkPath(_DeltaTime);
				CalMonsterDir();
				if (PrevDirStr != Walk.DirString)
				{
					MonsterRenderer->ChangeAnimation("Move" + Walk.DirString);
					PrevDirStr = Walk.DirString;
				}
				SummonCoolTime += _DeltaTime;
		},
			.End = [this]()
			{

			},
		});
}

void SandWraith::RangeAttackStateInit()
{
	MonsterFSM.CreateState(
		{
			.Name = "RangeAttack",
			.Start = [this]()
			{
				if (0.f <= GetTransform()->GetWorldPosition().x - RangeTargetFighter->GetTransform()->GetWorldPosition().x)
				{
					MonsterRenderer->GetTransform()->SetLocalNegativeScaleX();
				}
				else
				{
					MonsterRenderer->GetTransform()->SetLocalPositiveScaleX();
				}
				MonsterRenderer->ChangeAnimation("Idle");
			},
			.Update = [this](float _DeltaTime)
			{
				RangeTargetFighter = FindRangeTargetFighter();

				if (RangeTargetFighter != nullptr)
				{
					CalTargetPos();
				}

				if (CurHP <= 0)
				{
					State = MonsterState::Death;
				}

				if (RangeTargetFighter == nullptr)
				{
					State = MonsterState::Move;
					MonsterFSM.ChangeState("Move");
					return;
				}

				if (RangeTargetFighter->State == FighterState::Death)
				{
					State = MonsterState::Move;
					RangeTargetFighter = nullptr;
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
				if (AttackTime >= Data.RangedAttackRate)
				{
					if (0.f <= GetTransform()->GetWorldPosition().x - RangeTargetFighter->GetTransform()->GetWorldPosition().x)
					{
						MonsterRenderer->GetTransform()->SetLocalNegativeScaleX();
					}
					else
					{
						MonsterRenderer->GetTransform()->SetLocalPositiveScaleX();
					}
					AttackTime = 0.f;
					MonsterRenderer->ChangeAnimation("RangedAttack");
				}
				SummonCoolTime += _DeltaTime;
		},
			.End = [this]()
			{

			},
		});
}

void SandWraith::SummonStateInit()
{
	MonsterFSM.CreateState(
		{
			.Name = "Summon",
			.Start = [this]()
			{
				MonsterRenderer->ChangeAnimation("Summon");
				SummonCoolTime = 0.f;
			},
			.Update = [this](float _DeltaTime)
			{
				if (CurHP <= 0)
				{
					State = MonsterState::Death;
				}

				if (State == MonsterState::Death)
				{
					MonsterFSM.ChangeState("Death");
				}

				SummonCoolTime += _DeltaTime;
			},
			.End = [this]()
			{

			},
		});
}