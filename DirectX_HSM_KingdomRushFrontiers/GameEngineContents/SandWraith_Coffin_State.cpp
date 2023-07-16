#include "PrecompileHeader.h"
#include "SandWraith_Coffin.h"

#include <GameEngineCore\GameEngineSpriteRenderer.h>
#include "Fallen.h"

void SandWraith_Coffin::CoffinSpawnInit()
{
	CoffinFSM.CreateState({
		.Name = "Spawn",
		.Start = [this]()
		{
			CoffinRenderer->ChangeAnimation("Spawn");
		},
		.Update = [](float _DeltaTime)
		{

		},
		.End = []()
		{

		}
		});
}

void SandWraith_Coffin::CoffinUpdateInit()
{
	CoffinFSM.CreateState({
	.Name = "Update",
	.Start = [this]()
	{
		CoffinRenderer->ChangeAnimation("Update");
	},
	.Update = [this](float _DeltaTime)
	{
		Time += _DeltaTime;

		if (SpawnMobCount == 0)
		{
			State = CoffinState::Death;
			CoffinFSM.ChangeState("Death");
		}

		if (Time >= SpawnMobTime)
		{
			Time = 0.f;
			SummonFallen();
			--SpawnMobCount;
		}
	},
	.End = []()
	{

	}
		});
}

void SandWraith_Coffin::CoffinDeathInit()
{
	CoffinFSM.CreateState({
	.Name = "Death",
	.Start = [this]()
	{
		CoffinRenderer->ChangeAnimation("Death");

	},
	.Update = [](float _DeltaTime)
	{

	},
	.End = []()
	{

	}
		});
}