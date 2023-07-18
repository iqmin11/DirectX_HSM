#pragma once
#include "BaseShooter.h"

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
	
	void ChangeShooterRenderer(int _TowerLevel);
	void Attack();

protected:
	void Start() override;

private:
	float4 RenderScalse = { 64, 64, 1 };
	float Time = 0.0f;
};

