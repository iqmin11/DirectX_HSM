#include "PrecompileHeader.h"
#include "WaveButtons.h"

#include <GameEngineCore/GameEngineLevel.h>
#include "PlayStageLevel.h"
#include "NextWaveStartButton.h"
#include "PlayStageUI.h"
#include "BottomWaveButton.h"
#include "PlayStageLevel.h"

float WaveButtons::AutoStartTime = 40.f;
float WaveButtons::Time = 0.f;

float WaveButtons::GetTimeRatio()
{
	return Time/ AutoStartTime;
}

WaveButtons::WaveButtons()
{

}

WaveButtons::~WaveButtons()
{

}

std::shared_ptr<WaveButtons> WaveButtons::CreateWaveButtons(GameEngineLevel* _Level, std::vector<float4>& _Positions, int _Wave)
{
	std::weak_ptr<WaveButtons> ResultButtons(_Level->CreateActor<WaveButtons>());
	ResultButtons.lock()->Positions = _Positions;
	ResultButtons.lock()->Buttons.resize(ResultButtons.lock()->Positions.size());
	ResultButtons.lock()->Wave = _Wave;
	for (size_t i = 0; i < ResultButtons.lock()->Buttons.size(); i++)
	{
		ResultButtons.lock()->Buttons[i] = NextWaveStartButton::CreateButton(ResultButtons.lock().get(), _Wave);
		ResultButtons.lock()->Buttons[i]->GetTransform()->SetWorldPosition(ResultButtons.lock()->Positions[i]);
		ResultButtons.lock()->Buttons[i]->SetEvent([ResultButtons]()
			{
				Time = 0;
				dynamic_cast<PlayStageLevel*>(ResultButtons.lock()->GetLevel())->StartNextWave();
				for (size_t n = 0; n < ResultButtons.lock()->Buttons.size(); n++)
				{
					ResultButtons.lock()->Buttons[n]->Death();
				}
				ResultButtons.lock()->Buttons.clear();
				ResultButtons.lock()->Death();
				ResultButtons.lock()->GetLevel()->DynamicThis<PlayStageLevel>()->IsStartBattle = true;
			});
	}

	return ResultButtons.lock();
}

void WaveButtons::OnButtons()
{
	On();
	PlayStageUI::MainStageUI->SetWaveButtonEvent(Buttons[0]->GetEvent());
	BottomWaveButton::IsValid = true;
}

void WaveButtons::Start()
{

}

void WaveButtons::Update(float _DeltaTime)
{
	if (GetLevel()->DynamicThis<PlayStageLevel>()->IsPause)
	{
		return;
	}

	Time += _DeltaTime;
	if (Wave != 0)
	{
		if (AutoStartTime <= Time)
		{
			Time = 0.f;
			dynamic_cast<PlayStageLevel*>(GetLevel())->StartNextWave();
			Death();
		}
	}
	else
	{
		Time = AutoStartTime;
		//첫번쨰 웨이브인 경우
	}
}
