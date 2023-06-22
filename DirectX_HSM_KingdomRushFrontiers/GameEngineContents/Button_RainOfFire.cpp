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
}

void Button_RainOfFire::Update(float _DeltaTime)
{
	if (PlayManager::MainPlayer->GetState() == PlayerState::RainOfFire)
	{
		Render->SetTexture(SelectTextureName);
	}
	else
	{
		ContentsButton::Update(_DeltaTime);
		if (GameEngineInput::IsDown("1"))
		{
			GetEvent()();
		}
	}
}
