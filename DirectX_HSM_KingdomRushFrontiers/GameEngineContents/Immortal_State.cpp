#include "PrecompileHeader.h"
#include "Immortal.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseFighter.h"
#include "PopText.h"

void Immortal::DeathStateInit()
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

				SummonFallen();
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