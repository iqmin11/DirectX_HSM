#include "PrecompileHeader.h"
#include "BaseFighter.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RallyPoint.h"

BaseFighter::BaseFighter()
{

}

BaseFighter::~BaseFighter()
{

}

void BaseFighter::ResetRatio()
{
	Time = 0.f;
	Ratio = 0.f;
}

void BaseFighter::Start()
{
	FighterRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Mob);
	FighterRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "ReinforceA_0_Idle", .Loop = false });
	FighterRenderer->GetTransform()->SetWorldScale(FighterRendererScale);
	FighterRenderer->ChangeAnimation("Idle");
}

void BaseFighter::Update(float _DeltaTime)
{
	if (ParentRally != nullptr)
	{
		if (PrevPos != RallyPos)
		{	
			Time += _DeltaTime;
			Ratio = Time * (Speed / (RallyPos - PrevPos).Size());
			ActorPos = float4::LerpClamp(PrevPos, RallyPos, Ratio);
			GetTransform()->SetWorldPosition(ActorPos);
			if (Ratio >= 1)
			{
				PrevPos = RallyPos;
				Ratio = 0.f;
				Time = 0.f;
			}
		}

	}
}
