#include "PrecompileHeader.h"
#include "Button_Hero.h"

#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore\GameEngineUIRenderer.h>
#include "PlayManager.h"
#include "Hero_Alric.h"
#include "Hero_RallyPoint.h"
#include "Hero_Portrait.h"
#include "PlayStageLevel.h"

Button_Hero::Button_Hero()
{

}

Button_Hero::~Button_Hero()
{

}

std::shared_ptr<Button_Hero> Button_Hero::CreateButton(Hero_Portrait* _Parent)
{
	std::weak_ptr<Button_Hero> ResultButton(_Parent->GetLevel()->CreateActor<Button_Hero>());
	ResultButton.lock()->SetEvent([ResultButton]()
		{
			PlayManager::MainPlayer->SetState(PlayerState::Hero);
			ResultButton.lock()->SelectTexture->On();
		});
	ResultButton.lock()->ParentActor = _Parent;
	return ResultButton.lock();
}

std::weak_ptr<class GameEngineUIRenderer> Button_Hero::GetAlricPortrait()
{
	return ParentActor->GetAlricPortate();
}

void Button_Hero::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_4);
	Render->GetTransform()->SetWorldScale(ButtonRenderScale);
	SetTextureName("HeroPortraitFrame_Release.png", "HeroPortraitFrame_Hover.png", "HeroPortraitFrame_Hover.png");
	SelectTexture = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_3);
	SelectTexture->SetTexture("HeroPortraitFrame_Select.png");
	SelectTexture->GetTransform()->SetWorldScale(ButtonRenderScale);
	SelectTexture->Off();

	HeroReviveCoolRender = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_3);
	HeroReviveCoolRender->SetTexture("HeroReviveCoolRender.png");
	HeroReviveCoolRender->GetTransform()->SetWorldScale(HeroReviveCoolRenderScale);
	HeroReviveCoolRender->GetTransform()->SetLocalPosition(HeroReviveCoolRenderPos);

	HeroReviveAni = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_5);
	HeroReviveAni->CreateAnimation({ .AnimationName = "Revive", .SpriteName = "PortraitFrame_Revive", .FrameInter = 0.034f,.Loop = false });
	HeroReviveAni->SetAnimationStartEvent("Revive", 24, [this]()
		{
			HeroReviveAni->Off();
		});
	HeroReviveAni->GetTransform()->SetWorldScale(HeroPortraitFrameScale);
	HeroReviveAni->ChangeAnimation("Revive");
}

void Button_Hero::Update(float _DeltaTime)
{
	if (GetLevel()->DynamicThis<PlayStageLevel>()->IsPause)
	{
		return;
	}

	if (PlayManager::MainPlayer->GetState() == PlayerState::Hero)
	{
		ContentsButton::Update(_DeltaTime);
		if (!SelectTexture->IsUpdate())
		{
			SelectTexture->On();
		}
	}
	else if (PlayManager::MainPlayer->GetHeroState() == FighterState::Death)
	{
		if (Render->GetTexName() != ReleaseTextureName)
		{
			Render->SetTexture(ReleaseTextureName);
			GetAlricPortrait().lock()->ColorOptionValue.MulColor = {0.5f,0.5f,0.5f,1.f};
		}

		if (!HeroReviveCoolRender->IsUpdate())
		{
			HeroReviveCoolRender->On();
		}
		else
		{
			CoolRenderRatio = PlayManager::MainPlayer->GetHeroRally().lock()->GetHero().lock()->GetReviveTimeRatio();
			HeroReviveCoolRender->ImageClippingY(1.f - CoolRenderRatio, ClipYDir::Bot);
		}
	}
	else
	{
		if (SelectTexture->IsUpdate())
		{
			SelectTexture->Off();
		}
		if (HeroReviveCoolRender->IsUpdate())
		{
			HeroReviveCoolRender->Off();
			GetAlricPortrait().lock()->ColorOptionValue.MulColor = { 1.f,1.f,1.f,1.f };
			HeroReviveAni->On();
			HeroReviveAni->ChangeAnimation("Revive");
		}
		ContentsButton::Update(_DeltaTime);
		if (GameEngineInput::IsDown("Space"))
		{
			GetEvent()();
		}
	}
	
}
