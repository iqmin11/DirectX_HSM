#pragma once
#include <GameEngineCore/GameEngineActor.h>

class WaveButtons : public GameEngineActor
{
public:
	// construtor destructor
	WaveButtons();
	~WaveButtons();

	// delete Function
	WaveButtons(const WaveButtons& _Other) = delete;
	WaveButtons(WaveButtons&& _Other) noexcept = delete;
	WaveButtons& operator=(const WaveButtons& _Other) = delete;
	WaveButtons& operator=(WaveButtons&& _Other) noexcept = delete;

	static std::shared_ptr<WaveButtons> CreateWaveButtons(GameEngineLevel* _Level, std::vector<float4>& _Positions, int _Wave);
	std::vector<std::shared_ptr<class NextWaveStartButton>> GetButtons() const
	{
		return Buttons;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	int Wave = -1;
	std::vector<float4> Positions = std::vector<float4>();
	std::vector<std::shared_ptr<class NextWaveStartButton>> Buttons = std::vector<std::shared_ptr<class NextWaveStartButton>>();
	std::function<void()> Click = nullptr;
	float AutoStartTime = 40.f;
	float Time = 0.f;
};
