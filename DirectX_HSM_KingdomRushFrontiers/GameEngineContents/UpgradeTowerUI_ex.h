#pragma once
#include "UpgradeTowerUI.h"

class UpgradeTowerUI_ex : public UpgradeTowerUI
{
public:
	// construtor destructor
	UpgradeTowerUI_ex();
	~UpgradeTowerUI_ex();

	// delete Function
	UpgradeTowerUI_ex(const UpgradeTowerUI_ex& _Other) = delete;
	UpgradeTowerUI_ex(UpgradeTowerUI_ex&& _Other) noexcept = delete;
	UpgradeTowerUI_ex& operator=(const UpgradeTowerUI_ex& _Other) = delete;
	UpgradeTowerUI_ex& operator=(UpgradeTowerUI_ex&& _Other) noexcept = delete;
	
	static std::shared_ptr<UpgradeTowerUI_ex> CreateUpgradeTowerUI(class BaseTower* _ParentTower);

	std::shared_ptr<class RallyButton> AcRallyButton = nullptr;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RallyButtonLocPos = { 58,-58 };

};

