#include "PrecompileHeader.h"
#include "Button_CallReinforcement.h"

#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include "PlayManager.h"

Button_CallReinforcement::Button_CallReinforcement()
{

}

Button_CallReinforcement::~Button_CallReinforcement()
{

}

std::shared_ptr<Button_CallReinforcement> Button_CallReinforcement::CreateButton(GameEngineLevel* _Level)
{
	std::weak_ptr<Button_CallReinforcement> ResultButton(_Level->CreateActor<Button_CallReinforcement>());
	ResultButton.lock()->SetEvent([]()
		{
			PlayManager::MainPlayer->SetState(PlayerState::CallReinforcement);
		});
	return ResultButton.lock();
}

void Button_CallReinforcement::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_3);
	Render->GetTransform()->SetWorldScale(ButtonRenderScale);
	Render->CreateAnimation({ .AnimationName = "Revive", .SpriteName = "ReinforcementButton_Revive", .Loop = false});
	Render->SetAnimationStartEvent("Revive", 16, [this]()
		{
			Render->SetTexture(HoverTextureName);
		});
	SetTextureName("ReinforcementButton_Release.png", "ReinforcementButton_Hover.png", "ReinforcementButton_Hover.png");
	CooltimeRender = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_4);
	CooltimeRender->GetTransform()->SetWorldScale(ButtonRenderScale);
	CooltimeRender->SetTexture(ReleaseTextureName);
	CooltimeRender->ColorOptionValue.MulColor = { 0,0,0,0.5f };
	CooltimeRender->Off();
}

void Button_CallReinforcement::Update(float _DeltaTime)
{
	if (PlayManager::MainPlayer->GetState() == PlayerState::CallReinforcement)
	{
		Render->SetTexture(SelectTextureName);
	}
	else if (!PlayManager::MainPlayer->IsAvailable_CallReinforcement())
	{
		if (Render->GetTexName() != ReleaseTextureName)
		{
			Render->SetTexture(ReleaseTextureName);
			Render->ColorOptionValue.MulColor = { 0.5f,0.5f,0.5f,1.f };
		}

		if (!CooltimeRender->IsUpdate())
		{
			CooltimeRender->On();
		}
		else
		{
			CoolRenderRatio = PlayManager::MainPlayer->GetCallReinforcementCoolRatio();
			CooltimeRender->ImageClippingY(1.f - CoolRenderRatio, ClipYDir::Bot);
		}
	}
	else
	{
		if (CooltimeRender->IsUpdate())
		{
			CooltimeRender->Off();
			Render->ColorOptionValue.MulColor = { 1.f,1.f,1.f,1.f };
			Render->ChangeAnimation("Revive");
		}
		ContentsButton::Update(_DeltaTime);
		if (GameEngineInput::IsDown("2"))
		{
			GetEvent()();
		}
	}
}
