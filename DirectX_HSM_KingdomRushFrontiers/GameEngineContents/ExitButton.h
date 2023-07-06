#pragma once
#include "ContentsButton.h"

class ExitButton : public ContentsButton
{
public:
	// construtor destructor
	ExitButton();
	~ExitButton();

	// delete Function
	ExitButton(const ExitButton& _Other) = delete;
	ExitButton(ExitButton&& _Other) noexcept = delete;
	ExitButton& operator=(const ExitButton& _Other) = delete;
	ExitButton& operator=(ExitButton&& _Other) noexcept = delete;

	static std::shared_ptr<ExitButton> CreateButton(GameEngineActor* _Parent);
	
protected:
	void Start() override;

private:
	float4 ButtonScale = { 27,27,1 };
};

