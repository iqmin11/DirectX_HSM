#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

	static void ShootingBullet(GameEngineLevel* _Level, GameEngineActor* _ParentActor, float4& _TargetPos);
	void SetTargetPos(const float4& _TargetPos)
	{
		TargetPos = _TargetPos;
	}
	
	void SetParentPos(const float4& _ParentPos)
	{
		ParentPos = _ParentPos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BulletRenderer = nullptr;
	float4 ParentPos = float4::Zero;
	float4 TargetPos = float4::Zero;
	float BulletSpeed = 100.f;
	float Time = 0;
	float Ratio = 0;
};

