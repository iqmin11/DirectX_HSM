#pragma once
#include "ContentsButton.h"

class Defeat_RetryButton : public ContentsButton
{
public:
	// construtor destructor
	Defeat_RetryButton();
	~Defeat_RetryButton();

	// delete Function
	Defeat_RetryButton(const Defeat_RetryButton& _Other) = delete;
	Defeat_RetryButton(Defeat_RetryButton&& _Other) noexcept = delete;
	Defeat_RetryButton& operator=(const Defeat_RetryButton& _Other) = delete;
	Defeat_RetryButton& operator=(Defeat_RetryButton&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 Scale = { 152,63,1 };

	std::shared_ptr<class _101UIFontRenderer> FontRender = nullptr;
	std::string Continue = "재시작";
	std::string Font = "제주한라산";
	float FontScale = 30;
	float4 FontColor = { 0.9137254901960784f, 0.9137254901960784f, 0.6980392156862745f }; ;
	float4 FontLocPos = { 0,15 };
};

