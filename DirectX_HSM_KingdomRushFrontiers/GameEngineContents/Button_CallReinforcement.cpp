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

	SetTextureName("ReinforcementButton_Release.png", "ReinforcementButton_Hover.png", "ReinforcementButton_Hover.png");
	CooltimeRender = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_4);
	CooltimeRender->GetTransform()->SetWorldScale(CoolRenderScale);
	CooltimeRender->SetTexture("CoolRender.png");
	CooltimeRender->Off();

	ReviveAni = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_4);
	ReviveAni->CreateAnimation({ .AnimationName = "Revive", .SpriteName = "ReinforcementButton_Revive", .FrameInter = 0.05f, .Loop = false });
	ReviveAni->GetTransform()->SetWorldScale(ButtonRenderScale);
	ReviveAni->SetAnimationStartEvent("Revive", 16, [this]()
		{
			ReviveAni->Off();
		});
	ReviveAni->ChangeAnimation("Revive");
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
			ReviveAni->On();
			ReviveAni->ChangeAnimation("Revive");
		}
		ContentsButton::Update(_DeltaTime);
		if (GameEngineInput::IsDown("2"))
		{
			GetEvent()();
		}
	}
}
