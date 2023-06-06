#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsData.h"

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

protected:
	class BuildArea* ParentArea = nullptr;

	TowerData Data = {};
	std::shared_ptr<class GameEngineSpriteRenderer> TowerAreaRenderer = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> TowerRenderer = nullptr;

	std::shared_ptr<class TowerButton> UpgradeButton = nullptr;

private:
	float4 UpgradeUILocPos = { 0,15,-1000 };
};

