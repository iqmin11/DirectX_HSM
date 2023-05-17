#pragma once
#include "BaseTower.h"

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


	bool IsThereTarget();

private:
	float Time = 0.f;
	std::shared_ptr<class BaseMonster> FindTargetMonster();
	void CalTargetPos();
};

