#pragma once
#include "ContinueButton.h"

class Defeat_ExitButton : public ContinueButton
{
public:
	// construtor destructor
	Defeat_ExitButton();
	~Defeat_ExitButton();

	// delete Function
	Defeat_ExitButton(const Defeat_ExitButton& _Other) = delete;
	Defeat_ExitButton(Defeat_ExitButton&& _Other) noexcept = delete;
	Defeat_ExitButton& operator=(const Defeat_ExitButton& _Other) = delete;
	Defeat_ExitButton& operator=(Defeat_ExitButton&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 Scale = { 152,63,1 };

	std::shared_ptr<class _101UIFontRenderer> FontRender = nullptr;
	std::string Continue = "나가기";
	std::string Font = "제주한라산";
	float FontScale = 30;
	float4 FontColor = { 0.9137254901960784f, 0.9137254901960784f, 0.6980392156862745f }; ;
	float4 FontLocPos = { 0,15 };
};

