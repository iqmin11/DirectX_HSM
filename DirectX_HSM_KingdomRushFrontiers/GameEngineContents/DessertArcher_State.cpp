#include "PrecompileHeader.h"
#include "DessertArcher.h"

#include <GameEngineCore\GameEngineSpriteRenderer.h>
#include "BaseFighter.h"

void DessertArcher::MoveStateInit()
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

				if (RangeTargetFighter.lock() != nullptr && TargetFighter == nullptr)
				{
					State = MonsterState::RangeAttack;
					MonsterFSM.ChangeState("RangeAttack");
					return;
				}

				RangeTargetFighter.lock() = FindRangeTargetFighter();
				std::string PrevDirStr = Walk.DirString;
				WalkPath(_DeltaTime);
				CalMonsterDir();
				if (PrevDirStr != Walk.DirString)
				{
					MonsterRenderer->ChangeAnimation("Move" + Walk.DirString);
					PrevDirStr = Walk.DirString;
				}
			},
			.End = [this]()
			{

			},
		});
}

void DessertArcher::RangeAttackStateInit()
{
	MonsterFSM.CreateState(
		{
			.Name = "RangeAttack",
			.Start = [this]()
			{
				if (0.f <= GetTransform()->GetWorldPosition().x - RangeTargetFighter.lock()->GetTransform()->GetWorldPosition().x)
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

				if (RangeTargetFighter.lock() != nullptr)
				{
					CalTargetPos();
				}

				if (CurHP <= 0)
				{
					State = MonsterState::Death;
				}

				if (RangeTargetFighter.lock() == nullptr)
				{
					State = MonsterState::Move;
					MonsterFSM.ChangeState("Move");
					return;
				}

				if (RangeTargetFighter.lock()->State == FighterState::Death)
				{
					State = MonsterState::Move;
					RangeTargetFighter.lock() = nullptr;
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
					if (0.f <= GetTransform()->GetWorldPosition().x - RangeTargetFighter.lock()->GetTransform()->GetWorldPosition().x)
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
			},
			.End = [this]()
			{

			},
		});
}
