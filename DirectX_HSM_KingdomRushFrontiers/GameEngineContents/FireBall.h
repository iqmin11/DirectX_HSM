#pragma once
#include <GameEngineCore\GameEngineActor.h>
#include "ContentsEnum.h"

class FireBall : public GameEngineActor
{
public:
	// construtor destructor
	FireBall();
	~FireBall();

	// delete Function
	FireBall(const FireBall& _Other) = delete;
	FireBall(FireBall&& _Other) noexcept = delete;
	FireBall& operator=(const FireBall& _Other) = delete;
	FireBall& operator=(FireBall&& _Other) noexcept = delete;

	static void SummonFireBall(GameEngineLevel* _Level, float4 _TargetPos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> FireBallRenderer = nullptr;
	std::vector<std::shared_ptr<class GameEngineCollision>> FireBallCols = std::vector<std::shared_ptr<class GameEngineCollision>>();
	float4 RenderScale = { 128,128,1 };
	float4 ColScale = { 20,20,1 };
	float4 StartPos = float4::Zero;
	float4 TargetPos = float4::Zero;

	float Time = 0.f;
	float SmokeTime = 0.f;
	float Speed = 500.f;
	std::vector<float> Damage = std::vector<float>();

	void Attack();
};