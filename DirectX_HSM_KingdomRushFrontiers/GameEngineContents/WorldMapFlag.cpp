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
	FlagAnimation->CreateAnimation({.AnimationName = "NonClear_Appear", .SpriteName = "Flag_BeforClear_Appear", .FrameInter = 0.05f, .Loop = false});
	FlagAnimation->CreateAnimation({.AnimationName = "NonClear_Hover", .SpriteName = "Flag_BeforClear_Hover", .FrameInter = 0.05f, .Loop = false});
	FlagAnimation->CreateAnimation({.AnimationName = "NonClear_Release", .SpriteName = "Flag_BeforClear_Release", .FrameInter = 0.05f, .Loop = false});
	FlagAnimation->GetTransform()->SetWorldScale(RenderScale);
	FlagAnimation->SetAnimationStartEvent("NonClear_Appear", 32, [this]() 
		{
			FlagAnimation->ChangeAnimation("NonClear_Release");
			State = FlagState::Update;
		});
	FlagAnimation->ChangeAnimation("NonClear_Appear");
	
	Off();
}

void WorldMapFlag::Update(float _DeltaTime)
{
	if (State == FlagState::Update)
	{
		if (AcButton->GetState() != ButtonState::Release)
		{
			FlagAnimation->ChangeAnimation("NonClear_Hover");
		}
		else
		{
			FlagAnimation->ChangeAnimation("NonClear_Release");
		}
	}
}
