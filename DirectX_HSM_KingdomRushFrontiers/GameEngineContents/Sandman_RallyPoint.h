#pragma once
#include "RallyPoint.h"

class Sandman_RallyPoint : public RallyPoint
{
public:
	// construtor destructor
	Sandman_RallyPoint();
	~Sandman_RallyPoint();

	// delete Function
	Sandman_RallyPoint(const Sandman_RallyPoint& _Other) = delete;
	Sandman_RallyPoint(Sandman_RallyPoint&& _Other) noexcept = delete;
	Sandman_RallyPoint& operator=(const Sandman_RallyPoint& _Other) = delete;
	Sandman_RallyPoint& operator=(Sandman_RallyPoint&& _Other) noexcept = delete;

	static std::shared_ptr<Sandman_RallyPoint> CreateRallyPoint(class Hero_Alric* _Hero, const float4& _Pos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float DeathTime = 0.f;

	Hero_Alric* ParentHero = nullptr;

	void SetFighter();
	bool IsAllFightersDeath();
};

