#pragma once
#include "RallyPoint.h"

class Reinforcement_RallyPoint : public RallyPoint
{
public:
	// construtor destructor
	Reinforcement_RallyPoint();
	~Reinforcement_RallyPoint();

	// delete Function
	Reinforcement_RallyPoint(const Reinforcement_RallyPoint& _Other) = delete;
	Reinforcement_RallyPoint(Reinforcement_RallyPoint&& _Other) noexcept = delete;
	Reinforcement_RallyPoint& operator=(const Reinforcement_RallyPoint& _Other) = delete;
	Reinforcement_RallyPoint& operator=(Reinforcement_RallyPoint&& _Other) noexcept = delete;

	static std::shared_ptr<Reinforcement_RallyPoint> CreateRallyPoint(GameEngineLevel* _Level, const float4& _Pos, int _FighterCount);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	class FighterData* DataPtr = nullptr;
	float LiveTime = 0.f;

	void SetFighter(int _Count);

};

