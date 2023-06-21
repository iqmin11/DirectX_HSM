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
	float4 ButtonRenderScale = { 73,73,1 };
};

