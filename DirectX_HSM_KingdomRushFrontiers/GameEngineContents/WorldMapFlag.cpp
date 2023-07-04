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

void WorldMapFlag::FlagOn()
{
	On();
	FlagAnimation->ChangeAnimation("Appear");
}

std::shared_ptr<WorldMapFlag> WorldMapFlag::CreateFlag(GameEngineLevel* _Level, std::function<void()> _Click)
{
	std::shared_ptr<WorldMapFlag> LocFlag(_Level->CreateActor<WorldMapFlag>());
	LocFlag->AcButton = FlagButton::CreateButton(LocFlag.get(), _Click);
	return LocFlag;
}

void WorldMapFlag::Start()
{
	FlagAnimation = CreateComponent<GameEngineUIRenderer>(WorldMapUIOrder::WorldMapFlag);
	FlagAnimation->CreateAnimation({.AnimationName = "Appear", .SpriteName = "Flag_BeforClear_Appear", .FrameInter = 0.1f, .Loop = false});
	FlagAnimation->CreateAnimation({.AnimationName = "Hover", .SpriteName = "Flag_BeforClear_Hover", .FrameInter = 0.1f, .Loop = false});
	FlagAnimation->CreateAnimation({.AnimationName = "Release", .SpriteName = "Flag_BeforClear_Release", .FrameInter = 0.1f, .Loop = false});
	FlagAnimation->GetTransform()->SetWorldScale(RenderScale);
	FlagAnimation->SetAnimationStartEvent("Appear", 33, [this]() 
		{
			FlagAnimation->ChangeAnimation("Release");
			State = FlagState::Update;
		});

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
