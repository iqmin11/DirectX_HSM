#include "PrecompileHeader.h"
#include "Hero_Portrait.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include "PlayStageLevel.h"
#include "UIFontRenderer.h"
#include "Hero_RallyPoint.h"
#include "Hero_Alric.h"
#include "Button_Hero.h"


Hero_Portrait::Hero_Portrait()
{

}

Hero_Portrait::~Hero_Portrait()
{

}

std::weak_ptr<class GameEngineUIRenderer> Hero_Portrait::GetAlricPortate()
{
	return std::weak_ptr<class GameEngineUIRenderer>(AlricPortrait);
}

void Hero_Portrait::Start()
{
	HeroPortraitFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_4);
	HeroPortraitFrame->SetTexture("HeroPortraitFrame.png");
	HeroPortraitFrame->GetTransform()->SetWorldScale(HeroPortraitFrameScale);

	AlricPortrait = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_2);
	AlricPortrait->SetTexture("Alric_Portrait.png");
	AlricPortrait->GetTransform()->SetWorldScale(HeroPortraitFrameScale);

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

void Hero_Portrait::Update(float _DeltaTime)
{
	UpdateLifeBar();
}

void Hero_Portrait::UpdateLifeBar()
{
	std::weak_ptr<Hero_Alric>LocHero(GetLevel()->DynamicThis<PlayStageLevel>()->GetHero()->GetHero());
	HeroHpBar->ImageClippingX(LocHero.lock()->CurHP / LocHero.lock()->GetData().Hp, ClipXDir::Left);
}
