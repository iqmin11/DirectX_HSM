#pragma once
#include "BaseTower.h"
#include <GameEngineCore/GameEngineFSM.h>

class BaseShootingTower : public BaseTower
{
public:
	// construtor destructor
	BaseShootingTower();
	~BaseShootingTower();

	// delete Function
	BaseShootingTower(const BaseShootingTower& _Other) = delete;
	BaseShootingTower(BaseShootingTower&& _Other) noexcept = delete;
	BaseShootingTower& operator=(const BaseShootingTower& _Other) = delete;
	BaseShootingTower& operator=(BaseShootingTower&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	//std::shared_ptr<class GameEngineSpriteRenderer> TowerRangeRender = nullptr;
	std::shared_ptr<class BaseMonster> TargetMonster = nullptr;
	float4 TargetPos = float4::Zero;
	std::shared_ptr<class GameEngineCollision> RangeCol = nullptr;
	std::function<void()> Attack = nullptr;
	
	std::function<void()> IdleStart = nullptr;
	std::function<void(float)> IdleUpdate = nullptr;
	std::function<void()> IdleEnd = nullptr;


	bool IsThereTarget();

	void IdleStateInit(std::function<void()> _Start, std::function<void(float)> _Update, std::function<void()> _End);
	void AttackStateInit(std::function<void()> _Start, std::function<void(float)> _Update, std::function<void()> _End);

private:
	float Time = 0.f;
	GameEngineFSM ShootingTowerFSM = GameEngineFSM();

	std::shared_ptr<class BaseMonster> FindTargetMonster();
	void CalTargetPos();
};

