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
	float4 ButtonRenderScale = { 73,73,1 };
};
