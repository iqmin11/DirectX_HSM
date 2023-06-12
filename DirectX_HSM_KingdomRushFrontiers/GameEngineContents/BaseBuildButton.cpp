#include "PrecompileHeader.h"
#include "BaseBuildButton.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

BaseBuildButton::BaseBuildButton()
{

}

BaseBuildButton::~BaseBuildButton()
{

}

void BaseBuildButton::Start()
{
	ContentsButton::Start();
	GetTransform()->SetWorldScale(Scale);
	//Render->SetOrder(static_cast<int>(UIRenderOrder::TowerUIButton));
}

void BaseBuildButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
}
