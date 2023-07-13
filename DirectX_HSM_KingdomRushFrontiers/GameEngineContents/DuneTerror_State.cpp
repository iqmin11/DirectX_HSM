#include "PrecompileHeader.h"
#include "DuneTerror.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseFighter.h"
#include "PopText.h"

void DuneTerror::IdleStateInit()
{
	MonsterFSM.CreateState(
		{
			.Name = "Idle",
			.Start = [this]()
			{
				State = MonsterState::ComeUp;
				MonsterFSM.ChangeState("ComeUp");
			},
			.Update = [this](float _DeltaTime)
			{
			},
			.End = [this]()
			{
			},
		});
}

void DuneTerror::MoveStateInit()
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
				if (TargetFighter != nullptr)
				{
					State = MonsterState::ComeUp;
					MonsterFSM.ChangeState("ComeUp");
					return;
				}

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

void DuneTerror::AttackStateInit()
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
					State = MonsterState::GoDown;
					MonsterFSM.ChangeState("GoDown");
					return;
				}

				if (TargetFighter->State == FighterState::Death)
				{
					State = MonsterState::GoDown;
					TargetFighter = nullptr;
					MonsterFSM.ChangeState("GoDown");
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

void DuneTerror::DeathStateInit()
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

void DuneTerror::ComeUpStateInit()
{
	MonsterFSM.CreateState(
		{
			.Name = "ComeUp",
			.Start = [this]()
			{
				MonsterRenderer->ChangeAnimation("ComeUp");
			},
			.Update = [this](float _DeltaTime)
			{
				if (MonsterRenderer->IsAnimationEnd())
				{
					if (TargetFighter != nullptr)
					{
						State = MonsterState::Attack;
						MonsterFSM.ChangeState("Attack");
						return;
					}
					else if(TargetFighter == nullptr)
					{
						State = MonsterState::GoDown;
						MonsterFSM.ChangeState("GoDown");
						return;
					}
				}
			},
			.End = [this]()
			{
				Data.IsBurrow = false;
			},
		});
}

void DuneTerror::GoDownStateInit()
{
	MonsterFSM.CreateState(
		{
			.Name = "GoDown",
			.Start = [this]()
			{
				MonsterRenderer->ChangeAnimation("GoDown");
			},
			.Update = [this](float _DeltaTime)
			{
			},
			.End = [this]()
			{
				Data.IsBurrow = true;
			},
		});
}
