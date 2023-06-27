#pragma once
#include <GameEngineCore/GameEngineActor.h>

class WaveButtons : public GameEngineActor
{
public:
	
	static float GetTimeRatio();
	
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

	void OnButtons();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	int Wave = -1;
	std::vector<float4> Positions = std::vector<float4>();
	std::vector<std::shared_ptr<class NextWaveStartButton>> Buttons = std::vector<std::shared_ptr<class NextWaveStartButton>>();
	std::function<void()> Click = nullptr;

	static float AutoStartTime;
	static float Time;

};

