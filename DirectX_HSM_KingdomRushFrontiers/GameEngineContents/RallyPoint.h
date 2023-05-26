#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class RallyPoint : public GameEngineActor
{
public:

	// construtor destructor
	RallyPoint();
	~RallyPoint();

	// delete Function
	RallyPoint(const RallyPoint& _Other) = delete;
	RallyPoint(RallyPoint&& _Other) noexcept = delete;
	RallyPoint& operator=(const RallyPoint& _Other) = delete;
	RallyPoint& operator=(RallyPoint&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> TestRallyRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> RangeRender = nullptr;
	std::shared_ptr<class GameEngineCollision> RangeCol = nullptr;
	float Range = 60.f;

	std::vector<std::shared_ptr<GameEngineCollision>> ColMonsters = std::vector<std::shared_ptr<GameEngineCollision>>();
	std::vector<std::shared_ptr<class BaseFighter>> Fighters = std::vector<std::shared_ptr<class BaseFighter>>();


	//std::shared_ptr<class BaseFighter> Fighter0 = nullptr;
	//std::shared_ptr<class BaseFighter> Fighter1 = nullptr;
	//float4 Fighter0RallyPos = float4::Zero;
	//float4 Fighter1RallyPos = float4::Zero;

	std::shared_ptr<class BaseMonster> FindTargetMonster();
	float CalDistance(std::shared_ptr<class GameEngineCollision> _Monster);
	bool IsThereTarget();
	void SetRallyPos(float4 _Pos);
};

