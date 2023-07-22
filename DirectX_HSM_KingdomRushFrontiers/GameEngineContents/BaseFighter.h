#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "BaseMonster.h"
#include "ContentsData.h"

enum class FighterState
{
	Born,
	Idle,
	Move,
	TraceMonster,
	Attack,
	Return,
	Death,
	Revive,
	Skill0,
	Skill1
};

class BaseFighter : public GameEngineActor
{
	friend class RallyPoint;
	friend class Melee_RallyPoint;
	friend class Reinforcement_RallyPoint;
	friend class Hero_RallyPoint;
	friend class Sandman_RallyPoint;
public:
	// construtor destructor
	BaseFighter();
	~BaseFighter();

	// delete Function
	BaseFighter(const BaseFighter& _Other) = delete;
	BaseFighter(BaseFighter&& _Other) noexcept = delete;
	BaseFighter& operator=(const BaseFighter& _Other) = delete;
	BaseFighter& operator=(BaseFighter&& _Other) noexcept = delete;

	void SetParentRally(class RallyPoint* _Rally);
	

	void SetRallyTransform(GameEngineTransform* _Transform)
	{
		RallyTransform = _Transform;
	}

	void SetPrevPos(float4 _Pos)
	{
		PrevPos = _Pos;
	}

	void ResetRatio();
	
	FighterState State = FighterState::Idle;

	bool HaveITarget()
	{
		return TargetMonster != nullptr;
	}

	void SetTarget(std::shared_ptr<class BaseMonster> _Target)
	{
		TargetMonster = _Target;
		if (TargetMonster->TargetFighter == nullptr)
		{
			TargetMonster->TargetFighter = this;
		}
	}

	std::shared_ptr<class GameEngineCollision> GetFighterCol()
	{
		return FighterCol;
	}

	FighterState GetState() const
	{
		return State;
	}

	float CurHP = 0;

	FighterData GetData()
	{
		return Data;
	}

	bool IsHit = false;
	bool IsInvisible = false;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	FighterData Data = FighterData();

	std::shared_ptr<class GameEngineSpriteRenderer> FighterRenderer = nullptr;
	float4 FighterRendererScale = {64,64,1};
	std::shared_ptr<class BaseMonster> TargetMonster = nullptr;

	virtual int CalDamage() = 0
	{
		return GameEngineRandom::MainRandom.RandomInt(Data.Damage_min, Data.Damage_MAX);
	}

	std::function<void()> AttackTarget = nullptr;

	void IdleStateInit();
	void MoveStateInit();
	void TraceMonsterStateInit();
	void AttackStateInit();
	void ReturnStateInit();
	void DeathStateInit();
	GameEngineFSM FighterFSM = GameEngineFSM();

	RallyPoint* ParentRally = nullptr;

	GameEngineTransform* RallyTransform = nullptr;
	float4 ActorPos = float4::Zero;
	float4 PrevPos = float4::Zero;
	float4 SavePos = float4::Null;

	std::shared_ptr<class GameEngineCollision> FighterCol = nullptr;
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 18,18,1 };

	std::shared_ptr<class BaseMonster> PrevTarget = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> LifeBarBg = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LifeBar = nullptr;
	float4 LifeBarScale = { 20,2,1 };
	float4 LifeBarBgLocalPos = { 0,35,1 };
	float4 LifeBarLocalPos = { 0,35 };

	float Speed = 100.f;
	float Time = 0.f;
	float AttackTime = 100.f;
	float Ratio = 0.f;
	bool IsChangeTarget = false;

	float HealTime = 0.f;
	float DeathTime = 0.f;

	float PrevHP = 0.f;

	static GameEngineSoundPlayer AttackSound;
	std::vector<std::string> AttackSoundNames = std::vector<std::string>();

	virtual void MoveToRally(float _DeltaTime);
	void ReturnToRally(float _DeltaTime);
	virtual void MoveToTarget(float _DeltaTime);

	void UpdateLifeBar();
	void IdleAutoHeal(float _DeltaTime);

	void PlayAttackSound(const std::string_view& _Name);
	void PlayAttackSound();

private:


	//std::shared_ptr<class GameEngineCollision> BodyCollision = nullptr;
	//std::shared_ptr<class GameEngineCollision> RangeCollision = nullptr;


};

