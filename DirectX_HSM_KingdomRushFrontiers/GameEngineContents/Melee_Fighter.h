#pragma once
#include "BaseFighter.h"

class Melee_Fighter : public BaseFighter
{
public:
	// construtor destructor
	Melee_Fighter();
	~Melee_Fighter();

	// delete Function
	Melee_Fighter(const Melee_Fighter& _Other) = delete;
	Melee_Fighter(Melee_Fighter&& _Other) noexcept = delete;
	Melee_Fighter& operator=(const Melee_Fighter& _Other) = delete;
	Melee_Fighter& operator=(Melee_Fighter&& _Other) noexcept = delete;

	void ChangeFighter(int _TowerLevel);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void AttackTarget();
	int CalDamage() override;
	void SneakAttack();
	int CalSneakAttackDamage();

	int SneakAttack_min = 40;
	int SneakAttack_MAX = 40;

};

