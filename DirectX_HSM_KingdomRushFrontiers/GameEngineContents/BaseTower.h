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

	void SetAttackFunc(std::function<void()> _Attack)
	{
		Attack = _Attack;
	}

protected:
	TowerData Data = {};
	std::shared_ptr<class GameEngineSpriteRenderer> TowerRenderer = nullptr;
	float4 ActorPos = float4::Zero;
	std::shared_ptr<class GameEngineSpriteRenderer> TowerRangeRender = nullptr;
	std::list<std::shared_ptr<class BaseMonster>>* AccMonsterListPtr = nullptr;
	std::shared_ptr<class BaseMonster> TargetMonster = nullptr;
	float4 TargetPos = float4::Zero;

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 TestTargetPos = { 200, 200 };
	float Time = 0.f;
	
	std::function<void()> Attack = nullptr;

	//std::shared_ptr<class BaseMonster> FindTargetMonster();
};

