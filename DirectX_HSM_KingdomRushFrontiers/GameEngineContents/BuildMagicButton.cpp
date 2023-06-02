#include "PrecompileHeader.h"
#include "BuildMagicButton.h"

BuildMagicButton::BuildMagicButton()
{

}

BuildMagicButton::~BuildMagicButton()
{

}

void BuildMagicButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0003.png";
	HoverTextureName = "main_icons_0003.png";
	PressTextureName = "main_icons_0003.png";
}

void BuildMagicButton::Update(float _DeltaTime)
{
	BaseBuildButton::Update(_DeltaTime);
}
