#pragma once
#include "BaseMonster.h"

class SandWraith : public BaseMonster
{
public:
	// construtor destructor
	SandWraith();
	~SandWraith();

	// delete Function
	SandWraith(const SandWraith& _Other) = delete;
	SandWraith(SandWraith&& _Other) noexcept = delete;
	SandWraith& operator=(const SandWraith& _Other) = delete;
	SandWraith& operator=(SandWraith&& _Other) noexcept = delete;

	float4 GetRangeTargetPos();
	float GetBulletTime()
	{
		return BulletTime;
	}

	std::shared_ptr<class BaseFighter> GetRangeTargetFighter()
	{
		return RangeTargetFighter.lock();
	}

	float4 GetBulletStartPivotPos();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };
	float4 BoltStartPos = {0,20};

	std::shared_ptr<class GameEngineComponent> BulletStartPivot = nullptr;

	std::shared_ptr<class GameEngineCollision> RangeCol = nullptr;
	float Range = 140;

	std::weak_ptr<class BaseFighter> RangeTargetFighter;
	float4 RangeTargetPos = float4::Zero;

	std::shared_ptr<class BaseFighter> FindRangeTargetFighter();
	float BulletTime = 0.5f;

	float Time = 10.f;
	float SummonCoolTime = 0.0f;
	float SummonMaxCoolTime = 10.f;

	void CalTargetPos();

	void MoveStateInit() override;
	void RangeAttackStateInit();
	void SummonStateInit();
};
