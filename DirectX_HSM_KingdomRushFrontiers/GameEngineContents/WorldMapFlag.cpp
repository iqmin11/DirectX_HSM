#include "PrecompileHeader.h"
#include "WorldMapFlag.h"

#include <GameEngineCore\GameEngineUIRenderer.h>
#include <GameEngineCore\GameEngineLevel.h>
#include "FlagButton.h"

WorldMapFlag::WorldMapFlag()
{

}

WorldMapFlag::~WorldMapFlag()
{

}

std::shared_ptr<WorldMapFlag> WorldMapFlag::CreateFlag(GameEngineActor* _Parent, std::function<void()> _Click)
{
	std::shared_ptr<WorldMapFlag> LocFlag(_Parent->GetLevel()->CreateActor<WorldMapFlag>());
	LocFlag->GetTransform()->SetParent(_Parent->GetTransform());
	LocFlag->AcButton = FlagButton::CreateButton(LocFlag.get(), _Click);
	return LocFlag;
}

void WorldMapFlag::Start()
{
	FlagAnimation = CreateComponent<GameEngineUIRenderer>(WorldMapUIOrder::WorldMapFlag);
	FlagAnimation->CreateAnimation({.AnimationName = "Appear", .SpriteName = "Flag_BeforClear_Appear", .FrameInter = 0.075f, .Loop = false});
	FlagAnimation->CreateAnimation({.AnimationName = "Hover", .SpriteName = "Flag_BeforClear_Hover", .FrameInter = 0.075f, .Loop = false});
	FlagAnimation->CreateAnimation({.AnimationName = "Release", .SpriteName = "Flag_BeforClear_Release", .FrameInter = 0.075f, .Loop = false});
	FlagAnimation->GetTransform()->SetWorldScale(RenderScale);
	FlagAnimation->SetAnimationStartEvent("Appear", 32, [this]() 
		{
			FlagAnimation->ChangeAnimation("Release");
			State = FlagState::Update;
		});
	FlagAnimation->ChangeAnimation("Appear");

	Off();
}

void WorldMapFlag::Update(float _DeltaTime)
{
	if (State == FlagState::Start)
	{
		
	}
	else if (State == FlagState::Update)
	{
		if (AcButton->GetState() != ButtonState::Release)
		{
			FlagAnimation->ChangeAnimation("Hover");
		}
		else
		{
			FlagAnimation->ChangeAnimation("Release");
		}
	}
}
