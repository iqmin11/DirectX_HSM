#pragma once
#include <GameEngineCore/GameEngineActor.h>

class BaseShooter : public GameEngineActor
{
public:
	// construtor destructor
	BaseShooter();
	~BaseShooter();

	// delete Function
	BaseShooter(const BaseShooter& _Other) = delete;
	BaseShooter(BaseShooter&& _Other) noexcept = delete;
	BaseShooter& operator=(const BaseShooter& _Other) = delete;
	BaseShooter& operator=(BaseShooter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 ActorPos = float4::Zero;
	float4 RenderScalse = {32, 32};

	std::shared_ptr<class GameEngineSpriteRenderer> BaseShooterRenderer = nullptr;
	float AttackSpeed = 1.0f;
	float Time = 0.0f;

	void Attack();

	float4 TestTargetPos = {200,200};
};

