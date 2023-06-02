#include "PrecompileHeader.h"
#include "BaseBuildButton.h"

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
}

void BaseBuildButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
}
