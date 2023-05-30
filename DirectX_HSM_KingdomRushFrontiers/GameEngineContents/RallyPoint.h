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

	static std::shared_ptr<RallyPoint> CreateRallyPoint(GameEngineLevel* _Level, const float4& _Pos, int _FighterCount);

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
	std::vector<std::shared_ptr<class GameEngineComponent>> RallyPos = std::vector<std::shared_ptr<class GameEngineComponent>>();

	size_t PrevColCount = 0;
	bool IsChangeColCount = false;

	float CalDistance(std::shared_ptr<class GameEngineCollision> _Monster);
	bool IsThereTarget();
	void SetRallyPos();

	void SetPrevTarget();
	void FindTarget();
	void SetBoolChangeTarget();

	void ResetTargetMonster();

	void SetFighter(int _Count);
};

