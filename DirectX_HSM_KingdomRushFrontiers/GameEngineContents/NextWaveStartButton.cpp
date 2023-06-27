#include "PrecompileHeader.h"
#include "NextWaveStartButton.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include "PlayStageLevel.h"
#include "PlayStageUI.h"

NextWaveStartButton::NextWaveStartButton()
{

}

NextWaveStartButton::~NextWaveStartButton()
{

}

std::shared_ptr<NextWaveStartButton> NextWaveStartButton::CreateButton(GameEngineActor* _Parent, int _Wave)
{
	std::weak_ptr<NextWaveStartButton> ResultButton(_Parent->GetLevel()->CreateActor<NextWaveStartButton>());
	ResultButton.lock()->SetParentActor(_Parent);
	ResultButton.lock()->Wave = _Wave;
	return ResultButton.lock();
}

void NextWaveStartButton::Start()
{
	ContentsButton::Start();
	Render = CreateComponent<GameEngineUIRenderer>(UIRenderOrder::StageUI_3);
	GetTransform()->SetWorldScale(Scale);
	SelectedGlow = CreateComponent<GameEngineUIRenderer>();
	SelectedGlow->SetTexture("waveFlag_selected.png");
	SelectedGlow->GetTransform()->SetWorldScale(GlowScale);
	SelectedGlow->GetTransform()->SetParent(GetTransform());

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

	ButtonEffect();
	Time += _DeltaTime;
}

void NextWaveStartButton::ButtonEffect()
{
	if (State == ButtonState::Release)
	{
		SelectedGlow->Off();
	}
	else
	{
		SelectedGlow->On();
	}

	if (Time >= GameEngineMath::PIE2)
	{
		Time = 0.f;
	}
	float Ratio = (sin(Time * 8.f) + 1.f) / 2.f;
	GetTransform()->SetWorldScale(float4::LerpClamp(Scale * float4{ 0.9f,0.9f,0.9f }, Scale, Ratio));
}
