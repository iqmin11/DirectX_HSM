#include "PrecompileHeader.h"
#include "BuildRangedButton.h"

BuildRangedButton::BuildRangedButton()
{

}

BuildRangedButton::~BuildRangedButton()
{

}

void BuildRangedButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0001.png";
	HoverTextureName = "main_icons_0001.png";
	PressTextureName = "main_icons_0001.png";
}

void BuildRangedButton::Update(float _DeltaTime)
{
	BaseBuildButton::Update(_DeltaTime);
}
