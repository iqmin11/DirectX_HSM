#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsData.h"

#include <GameEnginePlatform\GameEngineSound.h>

enum class ConstructState
{
	Constructing,
	Complete
};

class BaseTower : public GameEngineActor
{
public:
	// construtor destructor
	BaseTower();
	~BaseTower();

	// delete Function
	BaseTower(const BaseTower& _Other) = delete;
	BaseTower(BaseTower&& _Other) noexcept = delete;
	BaseTower& operator=(const BaseTower& _Other) = delete;
	BaseTower& operator=(BaseTower&& _Other) noexcept = delete;

	const TowerData& GetData() const 
	{
		return Data;
	}

	std::shared_ptr<class UpgradeTowerUI> UpgradeUI = nullptr;

	virtual void ChangeTower(TowerEnum _Tower) = 0;
	void SellTower();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	class BuildArea* ParentArea = nullptr;

	TowerData Data = {};
	std::shared_ptr<class GameEngineSpriteRenderer> TowerAreaRenderer = nullptr;
	std::string TowerAreaRenderer_ReleaseName = "terrain_0004.png";
	std::string TowerAreaRenderer_HoverName = "terrain_0004_Hover.png";

	std::shared_ptr<class GameEngineSpriteRenderer> TowerRenderer = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> BuildBarBg = nullptr;
	float4 BuildBarBgScale = { 58,12,1 };
	std::shared_ptr<class GameEngineUIRenderer> BuildBar = nullptr;
	float4 BuildBarScale = { 54,8,1 };

	std::shared_ptr<class TowerButton> UpgradeButton = nullptr;
	ConstructState Construct = ConstructState::Constructing;
	float4 UpgradeUILocPos = { 0,15 };

	std::shared_ptr<class GameEngineSpriteRenderer> TowerRangeRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> NextLvRangeRender = nullptr;
	std::shared_ptr<class GameEngineCollision> RangeCol = nullptr;
	
	std::string TowerBuildSoundName = "Sound_TowerBuilding.ogg";
	std::vector<std::string> TauntSoundName = std::vector<std::string>();
	
	void PlayTowerCommandSound(const std::string_view& _Name);
	void PlayTauntSound(int _Level);

private:
	static GameEngineSoundPlayer TowerCommandSound;
};

