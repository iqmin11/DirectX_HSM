#pragma once
#include "BaseMonster.h"
class DessertArcher : public BaseMonster
{
public:
	// construtor destructor
	DessertArcher();
	~DessertArcher();

	// delete Function
	DessertArcher(const DessertArcher& _Other) = delete;
	DessertArcher(DessertArcher&& _Other) noexcept = delete;
	DessertArcher& operator=(const DessertArcher& _Other) = delete;
	DessertArcher& operator=(DessertArcher&& _Other) noexcept = delete;

	float4 GetRangeTargetPos();
	float GetBulletTime()
	{
		return BulletTime;
	}

	std::shared_ptr<class BaseFighter> GetRangeTargetFighter()
	{
		return RangeTargetFighter.lock();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };

	std::shared_ptr<class GameEngineCollision> RangeCol = nullptr;
	float Range = 140;
	
	std::weak_ptr<class BaseFighter> RangeTargetFighter;
	float4 RangeTargetPos = float4::Zero;

	std::shared_ptr<class BaseFighter> FindRangeTargetFighter();
	float BulletTime = 1.f;
	
	float Time = 10.f;

	void CalTargetPos();

	static GameEngineSoundPlayer DeathSound;

	void MoveStateInit() override;
	void RangeAttackStateInit();
};

