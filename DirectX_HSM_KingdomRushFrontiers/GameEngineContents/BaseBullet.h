#pragma once
#include <GameEngineCore/GameEngineActor.h>
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
		Data = _Data;
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
	


	bool IsBezier = false;
	float BulletTime = 1.f;
	TowerData* Data = nullptr;

private:
	float4 ParentPos = float4::Zero;
	float4 Mid0 = float4::Zero;
	float4 Mid1 = float4::Zero;
	float4 TargetPos = float4::Zero;
	float Time = 0.f;
	float Ratio = 0.f;


	void CalBezierBulletTransform(const float4& _P0, const float4& _P1, const float4& _P2, const float4& _P3, float _Ratio);
	void CalLerpBulletTransform(const float4& _P0, const float4& _P3, float _Ratio);

};

