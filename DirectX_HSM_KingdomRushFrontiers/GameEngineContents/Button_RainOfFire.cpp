#include "PrecompileHeader.h"
#include "Button_RainOfFire.h"

#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include "UIFontRenderer.h"
#include "PlayManager.h"
#include "PlayStageLevel.h"

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
	CooltimeRender->GetTransform()->SetWorldScale(CoolRenderScale);
	CooltimeRender->SetTexture("CoolRender.png");
	CooltimeRender->Off();

	ReviveAni = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_4);
	ReviveAni->CreateAnimation({ .AnimationName = "Revive", .SpriteName = "RainOfFireButton_Revive", .FrameInter = 0.05f, .Loop = false });
	ReviveAni->GetTransform()->SetWorldScale(ButtonRenderScale);
	ReviveAni->SetAnimationStartEvent("Revive", 16, [this]()
		{
			ReviveAni->Off();
		});
	ReviveAni->ChangeAnimation("Revive");
	
	NumFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_5);
	NumFrame->GetTransform()->SetWorldScale(NumFrameScale);
	NumFrame->GetTransform()->SetLocalPosition(NumFrameLocPos);
	NumFrame->SetTexture("NumFrame.png");

	NumFont = CreateComponent<UIFontRenderer>(UIRenderOrder::StageUI_6);
	NumFont->GetTransform()->SetLocalPosition({ 0,-25 });
	NumFont->SetFont("TOONISH");
	NumFont->SetScale(13.f);
	NumFont->SetColor(float4::White);
	NumFont->SetFontFlag(FW1_CENTER);
	NumFont->SetText("1");
}

void Button_RainOfFire::Update(float _DeltaTime)
{
	if (GetLevel()->DynamicThis<PlayStageLevel>()->IsPause)
	{
		return;
	}

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
			ReviveAni->On();
			ReviveAni->ChangeAnimation("Revive");
		}
		ContentsButton::Update(_DeltaTime);
		if (GameEngineInput::IsDown("1"))
		{
			GetEvent()();
		}
	}
}
