#pragma once
#include "BaseTower.h"
#include <GameEngineCore/GameEngineFSM.h>

class BaseShootingTower : public BaseTower
{
public:
	// construtor destructor
	BaseShootingTower();
	~BaseShootingTower() = 0 {};

	// delete Function
	BaseShootingTower(const BaseShootingTower& _Other) = delete;
	BaseShootingTower(BaseShootingTower&& _Other) noexcept = delete;
	BaseShootingTower& operator=(const BaseShootingTower& _Other) = delete;
	BaseShootingTower& operator=(BaseShootingTower&& _Other) noexcept = delete;

	float4& GetTargetPos()
	{
		return TargetPos;
	}

	const std::shared_ptr<class BaseMonster> GetTargetMonster() const
	{
		return TargetMonster;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	//std::shared_ptr<class GameEngineSpriteRenderer> TowerRangeRender = nullptr;

	std::shared_ptr<class BaseMonster> TargetMonster = nullptr;
	float4 TargetPos = float4::Zero;

	std::function<bool()> IsThereTargetFuncPtr = nullptr;
	std::function<std::shared_ptr<class BaseMonster>()> FindTargetMonsterFuncPtr = nullptr;

	virtual bool IsThereTarget();
	virtual std::shared_ptr<class BaseMonster> FindTargetMonster();
private:
	float Time = 10.f;

	void CalTargetPos();
};

