#pragma once
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

	//static std::shared_ptr<RallyPoint> CreateRallyPoint(GameEngineLevel* _Level, const float4& _Pos, int _FighterCount);
	void SetRallyPos(float4 _Pos);

	void ColOn();
	void ColOff();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	std::vector<std::shared_ptr<class BaseFighter>> Fighters = std::vector<std::shared_ptr<class BaseFighter>>();
	int FighterMaxCount = 0;
	std::vector<std::shared_ptr<class GameEngineComponent>> RallyPosCheckComponents = std::vector<std::shared_ptr<class GameEngineComponent>>();
	std::shared_ptr<class GameEngineCollision> RangeCol = nullptr;
	float Range = 60.f;
	
	bool IsThereTarget();
	virtual void FindTarget();


	std::vector<std::shared_ptr<GameEngineCollision>> ColMonsters = std::vector<std::shared_ptr<GameEngineCollision>>();

	size_t PrevColCount = 0;
	bool IsChangeColCount = false;

	float CalDistance(std::shared_ptr<class GameEngineCollision> _Monster);

	void SetPrevTarget();
	void SetBoolChangeTarget();

	void ResetTargetMonster();
	//void SetFighter(int _Count);
private:

};

