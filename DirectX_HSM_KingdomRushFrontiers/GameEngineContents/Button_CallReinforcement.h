#pragma once
#include "ContentsButton.h"

class Button_CallReinforcement : public ContentsButton
{
public:
	// construtor destructor
	Button_CallReinforcement();
	~Button_CallReinforcement();

	// delete Function
	Button_CallReinforcement(const Button_CallReinforcement& _Other) = delete;
	Button_CallReinforcement(Button_CallReinforcement&& _Other) noexcept = delete;
	Button_CallReinforcement& operator=(const Button_CallReinforcement& _Other) = delete;
	Button_CallReinforcement& operator=(Button_CallReinforcement&& _Other) noexcept = delete;
	
	static std::shared_ptr<Button_CallReinforcement> CreateButton(class GameEngineLevel* _Level);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::string SelectTextureName = "ReinforcementButton_Select.png";
	std::shared_ptr<class GameEngineUIRenderer> CooltimeRender = nullptr;
	float4 ButtonRenderScale = { 73,73,1 };
	float4 CoolRenderScale = { 53,53,1 };
	float CoolRenderRatio = 0.f;

	std::shared_ptr<class GameEngineUIRenderer> ReviveAni = nullptr;

	std::shared_ptr<class GameEngineUIRenderer> NumFrame = nullptr;
	float4 NumFrameScale = { 22,17,1 };
	float4 NumFrameLocPos = { 0,-31 };
	std::shared_ptr<class UIFontRenderer> NumFont = nullptr;
	float FontScale = 10.f;
};

