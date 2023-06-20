#pragma once
#include "BaseFighter.h"

class Sandman_Fighter : public BaseFighter
{
public:
	// construtor destructor
	Sandman_Fighter();
	~Sandman_Fighter();

	// delete Function
	Sandman_Fighter(const Sandman_Fighter& _Other) = delete;
	Sandman_Fighter(Sandman_Fighter&& _Other) noexcept = delete;
	Sandman_Fighter& operator=(const Sandman_Fighter& _Other) = delete;
	Sandman_Fighter& operator=(Sandman_Fighter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void AttackTarget();
	int CalDamage() override;

	float4 RanderScale = { 108,108,1 };
	float LiveTime = 0.f;

	void BornStateInit();
	void IdleStateInit();
	void MoveStartStateInit();
	void MoveStateInit();
	void MoveEndStateInit();
	void StartTraceMonsterStateInit();
	void TraceMonsterStateInit();
	void EndTraceMonsterStateInit();
	void AttackStateInit();
	void MoveDeathStateInit();
	void DeathStateInit();
};

