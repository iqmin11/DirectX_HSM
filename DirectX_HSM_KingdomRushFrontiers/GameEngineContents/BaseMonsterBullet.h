#pragma once
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsData.h"

class BaseMonsterBullet : public GameEngineActor
{
public:
	// construtor destructor
	BaseMonsterBullet();
	~BaseMonsterBullet();

	// delete Function
	BaseMonsterBullet(const BaseMonsterBullet& _Other) = delete;
	BaseMonsterBullet(BaseMonsterBullet&& _Other) noexcept = delete;
	BaseMonsterBullet& operator=(const BaseMonsterBullet& _Other) = delete;
	BaseMonsterBullet& operator=(BaseMonsterBullet&& _Other) noexcept = delete;

	void SetMonsterData(MonsterData* _Data)
	{
		Data = *_Data;
	}

protected:
	std::shared_ptr<class GameEngineSpriteRenderer> BulletRenderer = nullptr;

	void SetTargetPos(const float4& _TargetPos)
	{
		TargetPos = _TargetPos;
	}

	void SetParentPos(const float4& _ParentPos)
	{
		ParentPos = _ParentPos;
	}

	void CalBezierMid();

	void Start() override;
	void Update(float _DeltaTime) override;
	virtual int CalDamage() = 0
	{
		return GameEngineRandom::MainRandom.RandomInt(Data.RangedDamage_min, Data.RangedDamage_MAX);
	}

	bool IsBezier = false;
	float BulletTime = 1.f;
	MonsterData Data = MonsterData();
	std::function<void()> BulletHit = nullptr;
	std::function<void()> BulletMiss = nullptr;
	std::function<void()> BulletDeath = nullptr;
	float IsRot = false;
	std::shared_ptr<class BaseFighter> TargetFighter = nullptr;
	std::shared_ptr<class GameEngineCollision> BulletCol = nullptr;
	bool AmIMiss = false;

private:
	float4 ParentPos = float4::Zero;
	float4 Mid0 = float4::Zero;
	float4 Mid1 = float4::Zero;
	float4 TargetPos = float4::Zero;
	float Time = 0.f;
	float Ratio = 0.f;

	bool IsBulletDeath = false;

	void CalBezierBulletTransform(const float4& _P0, const float4& _P1, const float4& _P2, const float4& _P3, float _Ratio);
	void CalLerpBulletTransform(const float4& _P0, const float4& _P3, float _Ratio);
	void CalRotBulletRot(const float4& _P0, const float4& _P3, float _Ratio);
	void MissFunc();
	void HitFunc();

	bool IsThereTargetFighter();
	bool IsHitTargetFighter();
	bool IsMissTargetFighter();

};

