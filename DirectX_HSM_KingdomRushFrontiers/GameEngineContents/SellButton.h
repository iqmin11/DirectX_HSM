#pragma once
#include "ContentsButton.h"

class SellButton : public ContentsButton
{
public:
	// construtor destructor
	SellButton();
	~SellButton();

	// delete Function
	SellButton(const SellButton& _Other) = delete;
	SellButton(SellButton&& _Other) noexcept = delete;
	SellButton& operator=(const SellButton& _Other) = delete;
	SellButton& operator=(SellButton&& _Other) noexcept = delete;

	static std::shared_ptr<SellButton> CreateButton(class UpgradeTowerUI* _UI);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> ButtonGlow = nullptr;
	float4 Scale = { 47, 42, 1 };
	float4 GlowScale = { 52,47,1 };
};

