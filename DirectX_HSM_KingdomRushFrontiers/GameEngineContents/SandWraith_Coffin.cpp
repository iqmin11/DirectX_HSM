#include "PrecompileHeader.h"
#include "SandWraith_Coffin.h"

#include <GameEngineCore\GameEngineLevel.h>
#include <GameEngineCore\GameEngineSpriteRenderer.h>
#include "SandWraith.h"
#include "Fallen.h"

SandWraith_Coffin::SandWraith_Coffin()
{

}

SandWraith_Coffin::~SandWraith_Coffin()
{

}

void SandWraith_Coffin::SummonCoffin(SandWraith* _ParentActor)
{
	std::weak_ptr TempCoffin(_ParentActor->GetLevel()->CreateActor<SandWraith_Coffin>());
	TempCoffin.lock()->Walk = _ParentActor->GetWalk();
	TempCoffin.lock()->Walk = TempCoffin.lock()->Walk.GetNextPointWalkData();
	TempCoffin.lock()->GetTransform()->SetWorldPosition(TempCoffin.lock()->Walk.ActorPos + float4{0,0,-0.001f,0});
	if (TempCoffin.lock()->Walk.ActorPos.x - TempCoffin.lock()->Walk.PrevActorPos.x < 0)
	{
		TempCoffin.lock()->GetTransform()->SetLocalNegativeScaleX();
	}
	else
	{
		TempCoffin.lock()->GetTransform()->SetLocalPositiveScaleX();
	}
}

void SandWraith_Coffin::SummonFallen()
{
	std::weak_ptr<Fallen> Result(GetLevel()->CreateActor<Fallen>());
	Result.lock()->SetWalk(Walk);
	Result.lock()->GetTransform()->SetWorldPosition(Walk.ActorPos);
}

void SandWraith_Coffin::Start()
{
	CoffinRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	CoffinRenderer->GetTransform()->SetWorldScale(RenderScale);
	CoffinRenderer->CreateAnimation({.AnimationName = "Spawn", .SpriteName = "Coffin_Spawn", .FrameInter = 0.065f});
	CoffinRenderer->CreateAnimation({.AnimationName = "Update", .SpriteName = "Coffin_Update", .FrameInter = 0.065f });
	CoffinRenderer->CreateAnimation({.AnimationName = "Death", .SpriteName = "Coffin_Death", .FrameInter = 0.065f });

	CoffinRenderer->SetAnimationStartEvent("Spawn", 44, [this]()
		{
			State = CoffinState::Update;
			CoffinFSM.ChangeState("Update");
		});
	CoffinRenderer->SetAnimationStartEvent("Death", 6, [this]()
		{
			Death();
		});

	CoffinSpawnInit();
	CoffinUpdateInit();
	CoffinDeathInit();

	CoffinFSM.ChangeState("Spawn");
}

void SandWraith_Coffin::Update(float _DeltaTime)
{
	CoffinFSM.Update(_DeltaTime);
}


