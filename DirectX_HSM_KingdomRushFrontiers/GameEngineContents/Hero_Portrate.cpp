#include "PrecompileHeader.h"
#include "Hero_Portrate.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include "Button_Hero.h"

Hero_Portrate::Hero_Portrate()
{

}

Hero_Portrate::~Hero_Portrate()
{

}

void Hero_Portrate::Start()
{
	HeroPortrateFrame = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_2);
	HeroPortrateFrame->SetTexture("HeroPortrateFrame.png");
	HeroPortrateFrame->GetTransform()->SetWorldScale(HeroPortrateFrameScale);

	AlricPortrate = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_2);
	AlricPortrate->SetTexture("Alric_Portrate.png");
	AlricPortrate->GetTransform()->SetWorldScale(HeroPortrateFrameScale);

	HeroButton = Button_Hero::CreateButton(GetLevel());
	HeroButton->GetTransform()->SetParent(GetTransform());
}
