#pragma once
#include "ContentsButton.h"
#include "ContentsData.h"

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
	void SetPrice(TowerEnum _UpgTower);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	int Price = 0;

	float4 Scale = { 68, 60, 1 };
	TowerData ReturnNextTowerData();
	TowerEnum ReturnNextTowerEnum();
	std::shared_ptr<class GameEngineUIRenderer> ButtonGlow = nullptr;
	float4 GlowScale = { 75,68,1 };
	std::string InvalidTextureName = std::string();

	std::shared_ptr<class PriceTag> AcPriceTag = nullptr;
	void SetInvalid();
};

