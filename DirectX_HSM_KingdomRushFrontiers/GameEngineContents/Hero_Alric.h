#pragma once
#include "BaseFighter.h"
#include <GameEnginePlatform\GameEngineSound.h>

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
	
	std::vector<std::shared_ptr<GameEngineComponent>> GetSandmanPivot() const
	{
		return SandmanPivot;
	}

	float GetReviveTimeRatio()
	{
		return DeathTime / ReviveTime;
	}

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

	float4 RanderScale = { 217,217,1 };

	float FlurryCooltime = 6.f;
	std::shared_ptr<class GameEngineCollision> SummonCol = nullptr;
	float SummonRange = 200.f;
	float SummonCooltime = 10.f;
	std::vector<std::shared_ptr<GameEngineComponent>> SandmanPivot = std::vector<std::shared_ptr<GameEngineComponent>>();

	std::shared_ptr<class BaseMonster> SummonTargetMonster = nullptr;
	float4 SummonTargetPos = float4::Null;
	std::shared_ptr<class BaseMonster> FindTargetMonster();
	void CalTargetPos();
	bool IsThereSummonTarget();

	float ReviveTime = 20.f;
	
	GameEngineSoundPlayer CommandSound = GameEngineSoundPlayer();
	std::vector<std::string> CommandSoundNames = std::vector<std::string>();
	std::string DeathSoundName = "alric_taunt_death.ogg";
	std::string ReviveSoundName = "Level_up.ogg";
	std::string FlurrySoundName = "hero_alric_flurry.ogg";
	std::string SummonSoundName = "hero_alric_sandwarrior.ogg";

	void PlayHeroSound(const std::string_view& _Name);
};

