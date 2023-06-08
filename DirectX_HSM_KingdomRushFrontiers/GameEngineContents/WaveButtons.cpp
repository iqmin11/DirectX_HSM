#include "PrecompileHeader.h"
#include "WaveButtons.h"

#include <GameEngineCore/GameEngineLevel.h>
#include "PlayStageLevel.h"
#include "NextWaveStartButton.h"

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
		ResultButtons.lock()->Buttons[i]->GetTransform()->SetWorldScale({ 47, 46,1 });
		ResultButtons.lock()->Buttons[i]->GetTransform()->SetWorldPosition(ResultButtons.lock()->Positions[i]);
		ResultButtons.lock()->Buttons[i]->SetEvent([ResultButtons]()
			{
				dynamic_cast<PlayStageLevel*>(ResultButtons.lock()->GetLevel())->StartNextWave();
				for (size_t n = 0; n < ResultButtons.lock()->Buttons.size(); n++)
				{
					ResultButtons.lock()->Buttons[n]->Death();
				}
				ResultButtons.lock()->Buttons.clear();
				ResultButtons.lock()->Death();
			});
	}

	return ResultButtons.lock();
}

void WaveButtons::Start()
{

}

void WaveButtons::Update(float _DeltaTime)
{

}
