#pragma once
#include "ContentsButton.h"

class Button_RainOfFire : public ContentsButton
{
public:
	// construtor destructor
	Button_RainOfFire();
	~Button_RainOfFire();

	// delete Function
	Button_RainOfFire(const Button_RainOfFire& _Other) = delete;
	Button_RainOfFire(Button_RainOfFire&& _Other) noexcept = delete;
	Button_RainOfFire& operator=(const Button_RainOfFire& _Other) = delete;
	Button_RainOfFire& operator=(Button_RainOfFire&& _Other) noexcept = delete;

	static std::shared_ptr<Button_RainOfFire> CreateButton(class GameEngineLevel* _Level);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::string SelectTextureName = "RainOfFireButton_Select.png";
	std::shared_ptr<class GameEngineUIRenderer> CooltimeRender = nullptr;
	float4 ButtonRenderScale = { 73,73,1 };
	float4 CoolRenderScale = { 53,53,1 };
	float CoolRenderRatio = 0.f;

	std::shared_ptr<class GameEngineUIRenderer> ReviveAni = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> NumFrame = nullptr;
	float4 NumFrameScale = {22,17,1};
	float4 NumFrameLocPos = { 0,-31 };
	std::shared_ptr<class UIFontRenderer> NumFont = nullptr;
	float FontScale = 10.f;
};

