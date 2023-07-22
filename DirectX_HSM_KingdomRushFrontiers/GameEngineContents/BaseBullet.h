#pragma once
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "ContentsData.h"

class BaseBullet : public GameEngineActor
{
public:
	// construtor destructor
	BaseBullet();
	~BaseBullet();

	// delete Function
	BaseBullet(const BaseBullet& _Other) = delete;
	BaseBullet(BaseBullet&& _Other) noexcept = delete;
	BaseBullet& operator=(const BaseBullet& _Other) = delete;
	BaseBullet& operator=(BaseBullet&& _Other) noexcept = delete;

	//static void ShootingBullet(GameEngineLevel* _Level, GameEngineActor* _ParentActor);
	void SetTowerData(TowerData* _Data)
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
		return GameEngineRandom::MainRandom.RandomInt(Data.Damage_min, Data.Damage_MAX);
	}

	bool IsBezier = false;
	float BulletTime = 1.f;
	TowerData Data = TowerData();
	std::function<void()> BulletHit = nullptr;
	std::function<void()> BulletMiss = nullptr;
	std::function<void()> BulletDeath = nullptr;
	float IsRot = false;
	std::shared_ptr<class BaseMonster> TargetMonster = nullptr;
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
	
	bool IsThereTargetMonster();
	bool IsHitTargetMonster();
	bool IsMissTargetMonster();
};

