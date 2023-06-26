#include "PrecompileHeader.h"
#include "Hero_Portrate.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include "PlayStageLevel.h"
#include "UIFontRenderer.h"
#include "Hero_RallyPoint.h"
#include "Hero_Alric.h"
#include "Button_Hero.h"


Hero_Portrate::Hero_Portrate()
{

}

Hero_Portrate::~Hero_Portrate()
{

}

std::weak_ptr<class GameEngineUIRenderer> Hero_Portrate::GetAlricPortate()
{
	return std::weak_ptr<class GameEngineUIRenderer>(AlricPortrate);
}

void Hero_Portrate::Start()
{
	HeroPortrateFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_4);
	HeroPortrateFrame->SetTexture("HeroPortrateFrame.png");
	HeroPortrateFrame->GetTransform()->SetWorldScale(HeroPortrateFrameScale);

	AlricPortrate = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_2);
	AlricPortrate->SetTexture("Alric_Portrate.png");
	AlricPortrate->GetTransform()->SetWorldScale(HeroPortrateFrameScale);

	HeroButton = Button_Hero::CreateButton(this);
	HeroButton->GetTransform()->SetParent(GetTransform());

	HeroLevelRender = CreateComponent<UIFontRenderer>(UIRenderOrder::StageUI_5);
	HeroLevelRender->GetTransform()->SetLocalPosition(LevelFontLocPos);
	HeroLevelRender->SetFont("TOONISH");
	HeroLevelRender->SetScale(18.f);
	HeroLevelRender->SetColor(float4::White);
	HeroLevelRender->SetText("10");

	HeroHpBar = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_5);
	HeroHpBar->SetTexture("HeroUIHPBar.png");
	HeroHpBar->GetTransform()->SetWorldScale(HeroHpBarScale);
	HeroHpBar->GetTransform()->SetLocalPosition(HeroHpBarLocPos);
}

void Hero_Portrate::Update(float _DeltaTime)
{
	UpdateLifeBar();
}

void Hero_Portrate::UpdateLifeBar()
{
	std::weak_ptr<Hero_Alric>LocHero(GetLevel()->DynamicThis<PlayStageLevel>()->GetHero()->GetHero());
	HeroHpBar->ImageClippingX(LocHero.lock()->CurHP / LocHero.lock()->GetData().Hp, ClipXDir::Left);
}
