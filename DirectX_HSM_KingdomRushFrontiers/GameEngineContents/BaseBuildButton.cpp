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
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::TowerUIButton);
	GetTransform()->SetWorldScale(Scale);
}

void BaseBuildButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
}
