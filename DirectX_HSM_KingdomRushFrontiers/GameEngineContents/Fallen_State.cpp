#include "PrecompileHeader.h"
#include "Fallen.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

void Fallen::BornStateInit()
{
	MonsterFSM.CreateState({
		.Name = "Born",
		.Start = [this]()
		{
			MonsterRenderer->ChangeAnimation("Born");
			MonsterCol->Off();
		},
		.Update = [](float _DeltaTime)
		{
		},
		.End = [this]()
		{
			MonsterCol->On();
		}
	});
}