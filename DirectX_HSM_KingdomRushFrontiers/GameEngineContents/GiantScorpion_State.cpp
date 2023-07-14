#include "PrecompileHeader.h"
#include "GiantScorpion.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase\GameEngineRandom.h>

#include "BaseFighter.h"

void GiantScorpion::AttackStateInit()
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
					State = MonsterState::Move;
					MonsterFSM.ChangeState("Move");
					return;
				}

				if (TargetFighter->State == FighterState::Death)
				{
					State = MonsterState::Move;
					TargetFighter = nullptr;
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
					int RandInt = GameEngineRandom::MainRandom.RandomInt(0,1);
					AttackTime = 0.f;
					MonsterRenderer->ChangeAnimation("Attack" + std::to_string(RandInt));
				}
			},
			.End = [this]()
			{

			},
		});
}