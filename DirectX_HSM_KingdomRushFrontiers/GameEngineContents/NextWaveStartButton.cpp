#include "PrecompileHeader.h"
#include "NextWaveStartButton.h"

NextWaveStartButton::NextWaveStartButton()
{

}

NextWaveStartButton::~NextWaveStartButton()
{

}

void NextWaveStartButton::Start()
{
	ContentsButton::Start();
	ReleaseTextureName = "waveFlag_0001.png";
	HoverTextureName = "waveFlag_0001.png";
	PressTextureName = "waveFlag_0001.png";
}

void NextWaveStartButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
}
