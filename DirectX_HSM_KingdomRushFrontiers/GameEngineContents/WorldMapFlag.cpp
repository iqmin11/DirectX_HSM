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

void WorldMapFlag::SetClearData(int _StarCount)
{
	Data.Clear = true;
	Data.StarCount = _StarCount;
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
	StarRenderers.resize(3);
	for (size_t i = 0; i < StarRenderers.size(); i++)
	{
		StarRenderers[i] = CreateComponent<GameEngineUIRenderer>(WorldMapUIOrder::WorldMapFlagStar);
		StarRenderers[i]->GetTransform()->SetWorldScale({53,53,1});
		StarRenderers[i]->GetTransform()->SetLocalPosition({ -14.f + static_cast<float>(i)*13,59,0 });
		StarRenderers[i]->CreateAnimation({.AnimationName = "Star", .SpriteName = "FlagStar", .FrameInter = 0.05f, .Loop = false });
		StarRenderers[i]->ChangeAnimation("Star");
		StarRenderers[i]->Off();
	}
	
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

	FlagAnimation->CreateAnimation({ .AnimationName = "Clear_Appear", .SpriteName = "Flag_Clear_Appear", .FrameInter = 0.05f, .Loop = false });
	FlagAnimation->CreateAnimation({ .AnimationName = "Clear_Hover", .SpriteName = "Flag_Clear_Hover", .FrameInter = 0.05f, .Loop = false });
	FlagAnimation->CreateAnimation({ .AnimationName = "Clear_Release", .SpriteName = "Flag_Clear_Release", .FrameInter = 0.05f, .Loop = false });
	FlagAnimation->SetAnimationStartEvent("Clear_Appear", 16, [this]()
		{
			for (size_t i = 0; i < Data.StarCount; i++)
			{
				StarRenderers[i]->On();
			}
			State = FlagState::Update;
		});

	FlagAnimation->ChangeAnimation("NonClear_Appear");
	
	Off();
}

void WorldMapFlag::Update(float _DeltaTime)
{
	if (State == FlagState::Update)
	{
		if (Data.Clear == false)
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
		else
		{
			if (AcButton->GetState() != ButtonState::Release)
			{
				FlagAnimation->ChangeAnimation("Clear_Hover");
			}
			else
			{
				FlagAnimation->ChangeAnimation("Clear_Release");
			}
		}
	}
	else if(State == FlagState::Start)
	{
		if (Data.Clear == true)
		{
			if (ClearAndFirstUpdate)
			{
				ClearAndFirstUpdate = false;
				FlagAnimation->ChangeAnimation("Clear_Appear");
			}
		}
	}
}
