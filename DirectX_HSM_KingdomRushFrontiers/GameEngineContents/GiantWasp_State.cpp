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