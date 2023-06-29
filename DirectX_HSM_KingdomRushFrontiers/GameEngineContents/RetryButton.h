#pragma once
#include "ContentsButton.h"

class RetryButton : public ContentsButton
{
public:
	// construtor destructor
	RetryButton();
	~RetryButton();

	// delete Function
	RetryButton(const RetryButton& _Other) = delete;
	RetryButton(RetryButton&& _Other) noexcept = delete;
	RetryButton& operator=(const RetryButton& _Other) = delete;
	RetryButton& operator=(RetryButton&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 Scale = {171,71,1};
	std::shared_ptr<GameEngineUIRenderer> ChainRender = nullptr;
	float4 ChainRenderScale = {141,81,1};
	float4 ChainRenderLocPos = {0,20};

	std::shared_ptr<class UIFontRenderer> FontRender = nullptr;
	std::string Continue = "재도전";
	std::string Font = "제주한라산";
	float FontScale = 25;
	float4 FontColor = { 0.9137254901960784f, 0.9137254901960784f, 0.6980392156862745f }; ;
	float4 FontLocPos = { 0,15 };

};

