#pragma once
#include "ContentsButton.h"

class BottomWaveButton : public ContentsButton
{
public:
	static bool IsValid;
	// construtor destructor
	BottomWaveButton();
	~BottomWaveButton();

	// delete Function
	BottomWaveButton(const BottomWaveButton& _Other) = delete;
	BottomWaveButton(BottomWaveButton&& _Other) noexcept = delete;
	BottomWaveButton& operator=(const BottomWaveButton& _Other) = delete;
	BottomWaveButton& operator=(BottomWaveButton&& _Other) noexcept = delete;

	static std::shared_ptr<BottomWaveButton> CreateButton(class GameEngineLevel* _Level);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::string DisableTextureName = "WaveButton_Disable.png";
	float4 ButtonRenderScale = { 60,60,1 };

	GameEngineSoundPlayer WaveReadySound = GameEngineSoundPlayer();
};

