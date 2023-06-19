#pragma once
#include "RallyPoint.h"

class Hero_RallyPoint : public RallyPoint
{
public:
	// construtor destructor
	Hero_RallyPoint();
	~Hero_RallyPoint();

	// delete Function
	Hero_RallyPoint(const Hero_RallyPoint& _Other) = delete;
	Hero_RallyPoint(Hero_RallyPoint&& _Other) noexcept = delete;
	Hero_RallyPoint& operator=(const Hero_RallyPoint& _Other) = delete;
	Hero_RallyPoint& operator=(Hero_RallyPoint&& _Other) noexcept = delete;

	static std::shared_ptr<Hero_RallyPoint> CreateRallyPoint(GameEngineLevel* _Level, const float4& _Pos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void SetHero();
};

