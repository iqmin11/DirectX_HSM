#include "PrecompileHeader.h"
#include "NextWaveStartButton.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include "PlayStageLevel.h"

NextWaveStartButton::NextWaveStartButton()
{

}

NextWaveStartButton::~NextWaveStartButton()
{

}

std::shared_ptr<NextWaveStartButton> NextWaveStartButton::CreateButton(GameEngineLevel* _Level, int _Wave)
{
	std::weak_ptr<NextWaveStartButton> ResultButton(_Level->CreateActor<NextWaveStartButton>());
	ResultButton.lock()->Wave = _Wave;
	ResultButton.lock()->SetEvent([ResultButton]()
		{
			dynamic_cast<PlayStageLevel*>(ResultButton.lock()->GetLevel())->StartNextWave();
			ResultButton.lock()->Death();
		});
	return ResultButton.lock();
}

void NextWaveStartButton::Start()
{
	ContentsButton::Start();
	GetTransform()->SetWorldScale(Scale);
	ReleaseTextureName = "waveFlag_0001.png";
	HoverTextureName = "waveFlag_0001.png";
	PressTextureName = "waveFlag_0001.png";
	switch (State)
	{
	case ButtonState::Release:
		CurTextureName = ReleaseTextureName;
		break;
	case ButtonState::Press:
		CurTextureName = PressTextureName;
		break;
	case ButtonState::Hover:
		CurTextureName = HoverTextureName;
		break;
	default:
		break;
	}
	Render->SetTexture(CurTextureName);
}

void NextWaveStartButton::Update(float _DeltaTime)
{
	ContentsButton::Update(_DeltaTime);
	Time += _DeltaTime;
	
	ButtonEffect();
	
	if (Wave != 0)
	{
		if (AutoStartTime <= Time)
		{
			dynamic_cast<PlayStageLevel*>(GetLevel())->StartNextWave();
			Death(); 
		}
	}
	else
	{
		//첫번쨰 웨이브인 경우
	}
	
}

void NextWaveStartButton::ButtonEffect()
{
	float Ratio = (sin(Time * 8.f) + 1.f) / 2.f;
	GetTransform()->SetWorldScale(float4::LerpClamp(Scale * float4{ 0.9f,0.9f,0.9f }, Scale, Ratio));
}
