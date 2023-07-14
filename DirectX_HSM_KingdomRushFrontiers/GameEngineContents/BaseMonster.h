#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineFSM.h>

#include "ContentsEnum.h"
#include "ContentsData.h"


enum class MonsterState
{
	Idle,
	Move,
	Attack,
	Death,
	Born,
	ComeUp,
	GoDown,
	RangeAttack,
};

class BaseMonster : public GameEngineActor
{
protected:
	class WalkData
	{
	public:
		float4 ActorPos = float4::Zero;
		float4 PrevActorPos = float4::Zero;
		float4 ActorDir = float4::Zero;
		std::string DirString = std::string();

		std::vector<float4>* PathInfo = nullptr;
		std::vector<float4>::iterator CurPoint = std::vector<float4>::iterator();
		std::vector<float4>::iterator NextPoint = std::vector<float4>::iterator();
		std::vector<float4>::iterator LastPoint = std::vector<float4>::iterator();
		float Ratio = 0;
		float Time = 0;
	};

public:
	bool IsTestMonster = false;
	static std::list<std::weak_ptr<BaseMonster>> LiveMonsterList;
	static bool IsAllMonsterDead();
	static void LiveMonsterListForceRelease();

	// construtor destructor
	BaseMonster();
	~BaseMonster();

	// delete Function
	BaseMonster(const BaseMonster& _Other) = delete;
	BaseMonster(BaseMonster&& _Other) noexcept = delete;
	BaseMonster& operator=(const BaseMonster& _Other) = delete;
	BaseMonster& operator=(BaseMonster&& _Other) noexcept = delete;

	void SetHPBarPos(float _LocalY); // Base == 35

	void SetPathInfo(std::vector<float4>& _PathInfo)
	{
		Walk.PathInfo = &_PathInfo;
		Walk.CurPoint = Walk.PathInfo->begin();
		Walk.NextPoint = ++(Walk.PathInfo->begin());
		Walk.LastPoint = --(Walk.PathInfo->end());
	}

	const float4& GetLastPoint() const
	{
		return *Walk.LastPoint;
	}

	void SetWalk(const WalkData& _Walk)
	{
		Walk = _Walk;
	}

	static std::shared_ptr<BaseMonster> CreateMonster(const std::shared_ptr<GameEngineLevel> _Level, const MonsterEnum _Monster, std::vector<float4>& _PathInfo);
	float CalDistance();

	const float4& GetMonsterDir() const
	{
		return Walk.ActorDir;
	}

	const float GetMonsterSpeed() const
	{
		return Data.Speed;
	}

	std::shared_ptr<class GameEngineCollision> GetMonsterCol() const
	{
		return MonsterCol;
	}

	const WalkData& GetWalk() const
	{
		return Walk;
	}

	const MonsterData& GetData() const
	{
		return Data;
	}
	
	float CurHP = 0;
	HitState Hit = HitState::Etc;
	MonsterState State = MonsterState::Move;
	class BaseFighter* TargetFighter = nullptr;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void WalkToNextPoint(float _DeltaTime);
	void WalkPath(float _DeltaTime);
	void TestPath(float _DeltaTime);

	std::shared_ptr<class GameEngineSpriteRenderer> MonsterRenderer = nullptr;
	std::shared_ptr<class GameEngineCollision> MonsterCol = nullptr;
	MonsterData Data = MonsterData();

	GameEngineFSM MonsterFSM = GameEngineFSM();

	virtual void IdleStateInit();
	virtual void MoveStateInit();
	virtual void AttackStateInit();
	virtual void DeathStateInit();

	float DeathTime = 0.f;

	void Attack();
	float CalDamage();

	WalkData Walk = WalkData();

	std::shared_ptr<class GameEngineSpriteRenderer> LifeBarBg = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LifeBar = nullptr;
	float4 LifeBarScale = { 20,2,1 };
	float4 LifeBarBgLocalPos = { 0,35,1 };
	float4 LifeBarLocalPos = { 0,35 };

	float AttackTime = 100;

	void LiveMonsterListRelease();
	void CalMonsterDir();

	void UpdateLifeBar();
	void GiveBounty();

private:
	std::weak_ptr<class PlayStageLevel> ParentLevel;
	bool IsPause();
};

