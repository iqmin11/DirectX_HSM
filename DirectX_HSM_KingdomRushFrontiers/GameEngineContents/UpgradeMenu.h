#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UpgradeMenu : public GameEngineActor
{
public:
	// construtor destructor
	UpgradeMenu();
	~UpgradeMenu();

	// delete Function
	UpgradeMenu(const UpgradeMenu& _Other) = delete;
	UpgradeMenu(UpgradeMenu&& _Other) noexcept = delete;
	UpgradeMenu& operator=(const UpgradeMenu& _Other) = delete;
	UpgradeMenu& operator=(UpgradeMenu&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	float ScaleRatio = 900.f / 640.f;
	//float ScaleRatio = 720.f / 640.f;
	
	std::shared_ptr<class GameEngineSpriteRenderer> UpgradeBgLeft = nullptr;
	float4 UpgradeBgLeftScale = { 70.f, 656.f };
	std::shared_ptr<GameEngineSpriteRenderer> UpgradeBgMid = nullptr;
	float4 UpgradeBgMidScale = { 618.f, 618.f, 0.f, 1.f };
	float4 UpgradeBgMidPos= {-240.f,0.f };
	std::shared_ptr<GameEngineSpriteRenderer> UpgradeBgRight = nullptr;
	float4 UpgradeBgRightScale = { 70.f, 656.f };

	std::shared_ptr<GameEngineSpriteRenderer> UpgradeInfo = nullptr;
	float4 UpgradeInfoScale = {344, 444};
	float4 UpgradeInfoPos= {550,155};

	std::shared_ptr<GameEngineSpriteRenderer> UpgradeButton = nullptr;
	float4 UpgradeButtonScale = {341,114};
	float4 UpgradeButtonPos = {550,-217};

	std::shared_ptr<GameEngineSpriteRenderer> ResetButton = nullptr;
	float4 ResetButtonScale = {146,86};
	float4 ResetButtonPos = {415, -370};

	std::shared_ptr<GameEngineSpriteRenderer> DoneButton = nullptr;
	float4 DoneButtonScale = {146,86};
	float4 DoneButtonPos = {685, -370};

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> UpgradeBaseIcons = {};
	float4 BaseIconScale = {84.f, 86.f};
	float4 BaseIconStartPos = {-650.f,-330.f};
	float4 BaseIconInterval = {80.f,0.f};

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> UpgradeRangedTowerIcon = {};
	float4 UpgradeRangedTowerIconStartPos = { -650.f,-200.f };
	
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> UpgradeMeleeTowerIcon = {};
	float4 UpgradeMeleeTowerIconStartPos = { -486.f,-200.f };

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> UpgradeMagicTowerIcon = {};
	float4 UpgradeMagicTowerIconStartPos = { -322.f,-200.f };

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> UpgradeArtilleryTowerIcon = {};
	float4 UpgradeArtilleryTowerIconStartPos = { -158.f,-200.f };

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> UpgradeFireballIcon = {};
	float4 UpgradeFireballIconStartPos = { 6.f,-200.f };

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> UpgradeReinforcementTowerIcon = {};
	float4 UpgradeReinforcementTowerIconStartPos = { 170.f,-200.f };

	float4 UpgradeIconScale = {88, 86};
	float4 UpgradeIconInterval = { 0.f ,50.f };

	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> UpgradeGauges = {};

	float4 UpgradeGaugeScale = {8,440};
	float4 UpgradeGaugeStartPos = {-648,22};

	void SetUpgradeBgPos(float4& _Pos);

};

