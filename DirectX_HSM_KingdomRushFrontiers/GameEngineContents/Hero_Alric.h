#pragma once
#include "BaseFighter.h"

class Hero_Alric : public BaseFighter
{
public:
	// construtor destructor
	Hero_Alric();
	~Hero_Alric();

	// delete Function
	Hero_Alric(const Hero_Alric& _Other) = delete;
	Hero_Alric(Hero_Alric&& _Other) noexcept = delete;
	Hero_Alric& operator=(const Hero_Alric& _Other) = delete;
	Hero_Alric& operator=(Hero_Alric&& _Other) noexcept = delete;
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void IdleStateInit();
	void MoveStateInit();
	void TraceMonsterStateInit();
	void AttackStateInit();
	void ReturnStateInit();
	void DeathStateInit();
	void ReviveStateInit();
	void CastingSkill0StateInit();
	void CastingSkill1StateInit();

private:
	void AttackTarget();
	int CalDamage();
};

