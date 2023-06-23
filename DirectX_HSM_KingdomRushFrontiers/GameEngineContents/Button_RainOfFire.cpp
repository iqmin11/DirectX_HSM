#include "PrecompileHeader.h"
#include "Button_RainOfFire.h"

#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include "PlayManager.h"

Button_RainOfFire::Button_RainOfFire()
{

}

Button_RainOfFire::~Button_RainOfFire()
{

}

std::shared_ptr<Button_RainOfFire> Button_RainOfFire::CreateButton(GameEngineLevel* _Level)
{
	std::weak_ptr<Button_RainOfFire> ResultButton(_Level->CreateActor<Button_RainOfFire>());
	ResultButton.lock()->SetEvent([]()
		{
			PlayManager::MainPlayer->SetState(PlayerState::RainOfFire);
		});
	return ResultButton.lock();
}

void Button_RainOfFire::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_3);
	Render->GetTransform()->SetWorldScale(ButtonRenderScale);
	SetTextureName("RainOfFireButton_Release.png", "RainOfFireButton_Hover.png", "RainOfFireButton_Hover.png");
	CooltimeRender = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_4);
	CooltimeRender->GetTransform()->SetWorldScale(ButtonRenderScale);
	CooltimeRender->SetTexture(ReleaseTextureName);
	CooltimeRender->ColorOptionValue.MulColor = {0,0,0,0.5f};
	CooltimeRender->Off();
}

void Button_RainOfFire::Update(float _DeltaTime)
{
	if (PlayManager::MainPlayer->GetState() == PlayerState::RainOfFire)
	{
		Render->SetTexture(SelectTextureName);
	}
	else if (!PlayManager::MainPlayer->IsAvailable_RainOfFire())
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
			CoolRenderRatio = PlayManager::MainPlayer->GetRainOfFireCoolRatio();
			CooltimeRender->ImageClippingY(1.f - CoolRenderRatio,ClipYDir::Bot);
		}
	}
	else
	{
		if (CooltimeRender->IsUpdate())
		{
			CooltimeRender->Off();
			Render->ColorOptionValue.MulColor = { 1.f,1.f,1.f,1.f };
		}
		ContentsButton::Update(_DeltaTime);
		if (GameEngineInput::IsDown("1"))
		{
			GetEvent()();
		}
	}
}
