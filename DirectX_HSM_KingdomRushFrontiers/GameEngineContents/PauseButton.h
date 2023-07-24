#pragma once
#include "ContentsButton.h"

class PauseButton : public ContentsButton
{
public:
	// construtor destructor
	PauseButton();
	~PauseButton();

	// delete Function
	PauseButton(const PauseButton& _Other) = delete;
	PauseButton(PauseButton&& _Other) noexcept = delete;
	PauseButton& operator=(const PauseButton& _Other) = delete;
	PauseButton& operator=(PauseButton&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 PauseButtonScale = { 41,38,1 };
};

