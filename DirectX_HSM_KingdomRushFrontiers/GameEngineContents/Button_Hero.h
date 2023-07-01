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

	static std::shared_ptr<Button_Hero> CreateButton(class Hero_Portrait* _Parent);
	std::weak_ptr<class GameEngineUIRenderer>GetAlricPortrait();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	class Hero_Portrait* ParentActor = nullptr;

	std::shared_ptr<class GameEngineUIRenderer> SelectTexture = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> HeroReviveCoolRender = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> HeroReviveAni = nullptr;

	float4 ButtonRenderScale = { 119,119,1 };
	float4 HeroReviveCoolRenderScale = { 75,75,1 };
	float4 HeroReviveCoolRenderPos = { 1,5,0 };
	float4 HeroPortraitFrameScale = { 119,119,1 };

	float CoolRenderRatio = 0.f;
};

