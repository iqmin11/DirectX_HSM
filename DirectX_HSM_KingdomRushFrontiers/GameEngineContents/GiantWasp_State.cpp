#include "PrecompileHeader.h"
#include "GiantWasp.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseFighter.h"
#include "PopText.h"

void GiantWasp::MoveStateInit()
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

void GiantWasp::DeathStateInit()
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
				Shadow->Off();
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