#include "PrecompileHeader.h"
#include "Hero_Portrate.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
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

}
