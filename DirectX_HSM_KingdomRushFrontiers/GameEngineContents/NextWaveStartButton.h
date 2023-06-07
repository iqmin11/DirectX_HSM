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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

