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
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI);
	Render->GetTransform()->SetWorldScale(ButtonRenderScale);
	SetTextureName("ReinforcementButton_Release.png", "ReinforcementButton_Hover.png", "ReinforcementButton_Hover.png");
}

void Button_CallReinforcement::Update(float _DeltaTime)
{
	if (PlayManager::MainPlayer->GetState() == PlayerState::CallReinforcement)
	{
		Render->SetTexture(SelectTextureName);
	}
	else
	{
		ContentsButton::Update(_DeltaTime);
		if (GameEngineInput::IsDown("2"))
		{
			GetEvent()();
		}
	}
}
