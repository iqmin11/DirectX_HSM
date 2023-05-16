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


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	TowerData Data = {};
	std::shared_ptr<class GameEngineSpriteRenderer> TowerRenderer = nullptr;
	float4 ActorPos = float4::Zero;
	//std::shared_ptr<class GameEngineSpriteRenderer> TowerRangeRender = nullptr;
	std::list<std::shared_ptr<class BaseMonster>>* AccMonsterListPtr = nullptr;
	std::shared_ptr<class BaseMonster> TargetMonster = nullptr;
	float4 TargetPos = float4::Zero;
	std::shared_ptr<class GameEngineCollision> RangeCol = nullptr;

	bool IsThereTarget();


private:
	float4 TestTargetPos = { 200, 200 };
	float Time = 0.f;
	
	std::shared_ptr<class BaseMonster> FindTargetMonster();
	void CalTargetPos();
};

