#pragma once
#include "BaseFighter.h"

class Reinforcement_Fighter : public BaseFighter
{
public:
	// construtor destructor
	Reinforcement_Fighter();
	~Reinforcement_Fighter();

	// delete Function
	Reinforcement_Fighter(const Reinforcement_Fighter& _Other) = delete;
	Reinforcement_Fighter(Reinforcement_Fighter&& _Other) noexcept = delete;
	Reinforcement_Fighter& operator=(const Reinforcement_Fighter& _Other) = delete;
	Reinforcement_Fighter& operator=(Reinforcement_Fighter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void AttackTarget();
	int CalDamage() override;

	float4 ReinforcementRenderScale = { 128,128,1 };
	void SetAnimation_A();
	void SetAnimation_B();
	void SetAnimation_C();

	float LiveTime = 0.f;
};

