#pragma once
#include "ContentsButton.h"

class Button_Hero : public ContentsButton
{
public:
	// construtor destructor
	Button_Hero();
	~Button_Hero();

	// delete Function
	Button_Hero(const Button_Hero& _Other) = delete;
	Button_Hero(Button_Hero&& _Other) noexcept = delete;
	Button_Hero& operator=(const Button_Hero& _Other) = delete;
	Button_Hero& operator=(Button_Hero&& _Other) noexcept = delete;

	static std::shared_ptr<Button_Hero> CreateButton(class GameEngineLevel* _Level);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> SelectTexture = nullptr;
	float4 ButtonRenderScale = { 119,119,1 };
};

