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

protected:
	void Start() override;

private:
	float4 RenderScalse = { 32, 32 };
	void Attack();
};

