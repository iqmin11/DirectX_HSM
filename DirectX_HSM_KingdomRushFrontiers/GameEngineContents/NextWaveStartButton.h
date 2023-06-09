#pragma once
#include "ContentsButton.h"

class NextWaveStartButton : public ContentsButton
{
public:
	// construtor destructor
	NextWaveStartButton();
	~NextWaveStartButton();

	// delete Function
	NextWaveStartButton(const NextWaveStartButton& _Other) = delete;
	NextWaveStartButton(NextWaveStartButton&& _Other) noexcept = delete;
	NextWaveStartButton& operator=(const NextWaveStartButton& _Other) = delete;
	NextWaveStartButton& operator=(NextWaveStartButton&& _Other) noexcept = delete;

	static std::shared_ptr<NextWaveStartButton> CreateButton(class GameEngineActor* _Parent, int _Wave);

	int GetWave() const
	{
		return Wave;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> SelectedGlow = nullptr;
	float4 Scale = { 52, 52,1 };
	int Wave = -1;
	float Time = 0.f;
	
	std::shared_ptr<class ContentsUIRenderer> NextWaveGaugeRender = nullptr;

	void ButtonEffect();
};

