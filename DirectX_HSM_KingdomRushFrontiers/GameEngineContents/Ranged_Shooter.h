#pragma once
#include "BaseShooter.h"
#include <GameEngineCore/GameEngineFSM.h>

enum class ShooterState
{
	Idle,
	Attack
};

class Ranged_Shooter : public BaseShooter
{
public:
	// construtor destructor
	Ranged_Shooter();
	~Ranged_Shooter();

	// delete Function
	Ranged_Shooter(const Ranged_Shooter& _Other) = delete;
	Ranged_Shooter(Ranged_Shooter&& _Other) noexcept = delete;
	Ranged_Shooter& operator=(const Ranged_Shooter& _Other) = delete;
	Ranged_Shooter& operator=(Ranged_Shooter&& _Other) noexcept = delete;
	
	void ChangeShooterRenderer(TowerEnum _Tower);
	void Attack(float _DeltaTime);
	ShooterState StateValue = ShooterState::Idle;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScalse = { 32, 32 };
	GameEngineFSM ShooterFSM = GameEngineFSM();
	bool IsShootBullet = false;
	float Time = 0.0f;

	void IdleStateInit();
	void AttackStateInit();
};

