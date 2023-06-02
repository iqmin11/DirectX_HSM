#include "PrecompileHeader.h"
#include "BuildMeleeButton.h"

BuildMeleeButton::BuildMeleeButton()
{

}

BuildMeleeButton::~BuildMeleeButton()
{

}

void BuildMeleeButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0002.png";
	HoverTextureName = "main_icons_0002.png";
	PressTextureName = "main_icons_0002.png";
}

void BuildMeleeButton::Update(float _DeltaTime)
{
	BaseBuildButton::Update(_DeltaTime);
}
