#pragma once
#include "BaseShooter.h"

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
	void Attack();

protected:
	void Start() override;

private:
	float4 RenderScalse = { 32, 32 };

	ShooterState StateValue = ShooterState::Idle;

	void ChangeState(ShooterState _StateValue);
	void UpdateState(float _DeltaTime);

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void AttackStart();
	void AttackUpdate(float _DeltaTime);
	void AttackEnd();
};

