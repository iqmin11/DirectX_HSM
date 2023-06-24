#pragma once
#include "ContentsButton.h"

class BaseBuildButton : public ContentsButton
{
public:
	// construtor destructor
	BaseBuildButton();
	~BaseBuildButton();

	// delete Function
	BaseBuildButton(const BaseBuildButton& _Other) = delete;
	BaseBuildButton(BaseBuildButton&& _Other) noexcept = delete;
	BaseBuildButton& operator=(const BaseBuildButton& _Other) = delete;
	BaseBuildButton& operator=(BaseBuildButton&& _Other) noexcept = delete;

	//static std::shared_ptr<BaseBuildButton> CreateButton(class BuildTowerUI* _UI);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> ButtonGlow = nullptr;

	float4 Scale = { 68,60,1 };
	float4 GlowScale = { 75,68,1 };
};

