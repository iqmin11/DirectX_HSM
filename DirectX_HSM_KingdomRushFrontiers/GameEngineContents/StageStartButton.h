#pragma once
#include "ContentsButton.h"

class StageStartButton : public ContentsButton
{
public:
	// construtor destructor
	StageStartButton();
	~StageStartButton();

	// delete Function
	StageStartButton(const StageStartButton& _Other) = delete;
	StageStartButton(StageStartButton&& _Other) noexcept = delete;
	StageStartButton& operator=(const StageStartButton& _Other) = delete;
	StageStartButton& operator=(StageStartButton&& _Other) noexcept = delete;

	static std::shared_ptr<StageStartButton> CreateButton(GameEngineActor* _Parent);

protected:
	void Start() override;
private:
	float4 ButtonScale = { 96,83,1 };
};

