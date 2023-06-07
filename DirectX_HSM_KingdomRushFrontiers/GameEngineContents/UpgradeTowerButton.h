#pragma once
#include "ContentsButton.h"

class UpgradeTowerButton : public ContentsButton
{
public:
	// construtor destructor
	UpgradeTowerButton();
	~UpgradeTowerButton();

	// delete Function
	UpgradeTowerButton(const UpgradeTowerButton& _Other) = delete;
	UpgradeTowerButton(UpgradeTowerButton&& _Other) noexcept = delete;
	UpgradeTowerButton& operator=(const UpgradeTowerButton& _Other) = delete;
	UpgradeTowerButton& operator=(UpgradeTowerButton&& _Other) noexcept = delete;

	static std::shared_ptr<UpgradeTowerButton> CreateButton(class UpgradeTowerUI* _UI);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 Scale = { 68, 60, 1 };
	TowerEnum ReturnUpgradeTowerEnum();
};

