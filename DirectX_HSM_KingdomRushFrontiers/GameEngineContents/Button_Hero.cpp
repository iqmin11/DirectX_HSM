#include "PrecompileHeader.h"
#include "Button_Hero.h"

#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include "PlayManager.h"

Button_Hero::Button_Hero()
{

}

Button_Hero::~Button_Hero()
{

}

std::shared_ptr<Button_Hero> Button_Hero::CreateButton(GameEngineLevel* _Level)
{
	std::weak_ptr<Button_Hero> ResultButton(_Level->CreateActor<Button_Hero>());
	ResultButton.lock()->SetEvent([ResultButton]()
		{
			PlayManager::MainPlayer->SetState(PlayerState::Hero);
			ResultButton.lock()->SelectTexture->On();
		});
	return ResultButton.lock();
}

void Button_Hero::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_4);
	Render->GetTransform()->SetWorldScale(ButtonRenderScale);
	SetTextureName("HeroPortrateFrame_Release.png", "HeroPortrateFrame_Hover.png", "HeroPortrateFrame_Hover.png");
	SelectTexture = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_3);
	SelectTexture->SetTexture("HeroPortrateFrame_Select.png");
	SelectTexture->GetTransform()->SetWorldScale(ButtonRenderScale);
	SelectTexture->Off();
}

void Button_Hero::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
	if (GameEngineInput::IsDown("Space"))
	{
		GetEvent()();
	}
}
