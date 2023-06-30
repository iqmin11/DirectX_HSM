#pragma once
#include "ContentsButton.h"

class ContinueButton : public ContentsButton
{
public:
	// construtor destructor
	ContinueButton();
	~ContinueButton();

	// delete Function
	ContinueButton(const ContinueButton& _Other) = delete;
	ContinueButton(ContinueButton&& _Other) noexcept = delete;
	ContinueButton& operator=(const ContinueButton& _Other) = delete;
	ContinueButton& operator=(ContinueButton&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 Scale = { 209, 80 };
	std::shared_ptr<class _101UIRenderer> ChainRender = nullptr;
	float4 ChainRenderScale = { 172,99,1 };
	float4 ChainRenderLocPos = { 0, 60 };

	std::shared_ptr<class _101UIFontRenderer> FontRender = nullptr;
	std::string Continue = "계속하기";
	std::string Font = "제주한라산";
	float FontScale = 30;
	float4 FontColor = { 0.9137254901960784f, 0.9137254901960784f, 0.6980392156862745f }; ;
	float4 FontLocPos = {0,15};

};

