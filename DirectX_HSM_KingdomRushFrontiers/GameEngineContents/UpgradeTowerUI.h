#pragma once
#include "BaseTowerUI.h"

class UpgradeTowerUI : public BaseTowerUI
{
public:
	
	// construtor destructor
	UpgradeTowerUI();
	~UpgradeTowerUI();

	// delete Function
	UpgradeTowerUI(const UpgradeTowerUI& _Other) = delete;
	UpgradeTowerUI(UpgradeTowerUI&& _Other) noexcept = delete;
	UpgradeTowerUI& operator=(const UpgradeTowerUI& _Other) = delete;
	UpgradeTowerUI& operator=(UpgradeTowerUI&& _Other) noexcept = delete;

	static std::shared_ptr<UpgradeTowerUI> CreateUpgradeTowerUI(class BaseTower* _ParentTower);

	BaseTower* GetParentArea()
	{
		return ParentTower;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	BaseTower* ParentTower = nullptr;

	std::shared_ptr<class BuildRangedButton> AcBuildRangedButton = nullptr;
	std::shared_ptr<class BuildMeleeButton> AcBuildMeleeButton = nullptr;

	std::shared_ptr<class BuildMagicButton> AcBuildMagicButton = nullptr;
	std::shared_ptr<class BuildArtilleryButton> AcBuildArtilleryButton = nullptr;

	float4 UpgradeButtonLocPos = { 0,81,-10 };
	float4 SellButtonLocPos = { 0,-81,-10 };
	//float4 Button2LocPos = { -58,-58,-10 };
	//float4 Button3LocPos = { 58,-58,-10 };
};

