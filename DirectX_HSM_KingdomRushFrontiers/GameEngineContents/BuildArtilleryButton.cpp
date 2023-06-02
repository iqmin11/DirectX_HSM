#include "PrecompileHeader.h"
#include "BuildArtilleryButton.h"

BuildArtilleryButton::BuildArtilleryButton()
{

}

BuildArtilleryButton::~BuildArtilleryButton()
{

}

void BuildArtilleryButton::Start()
{
	BaseBuildButton::Start();
	ReleaseTextureName = "main_icons_0004.png";
	HoverTextureName = "main_icons_0004.png";
	PressTextureName = "main_icons_0004.png";
}

void BuildArtilleryButton::Update(float _DeltaTime)
{
	BaseBuildButton::Update(_DeltaTime);
}
