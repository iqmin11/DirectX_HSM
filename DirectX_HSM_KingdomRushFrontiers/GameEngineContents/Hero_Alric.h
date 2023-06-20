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
	void CastingSkill1StateInit();

private:
	void AttackTarget();
	void AttackFlurry();
	int CalDamage();

	float FlurryCooltime = 0.f;
	std::shared_ptr<class GameEngineCollision> SummonCol = nullptr;
	float SummonRange = 200.f;
	float SummonCooltime = 0.f;

	std::shared_ptr<class BaseMonster> SummonTargetMonster = nullptr;
	float4 SummonTargetPos = float4::Null;
	std::shared_ptr<class BaseMonster> FindTargetMonster();
	void CalTargetPos();
	bool IsThereSummonTarget();
};

