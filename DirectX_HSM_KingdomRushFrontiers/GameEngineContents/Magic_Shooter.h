#pragma once
#include "BaseShooter.h"

class Magic_Shooter : public BaseShooter
{
public:
	// construtor destructor
	Magic_Shooter();
	~Magic_Shooter();

	// delete Function
	Magic_Shooter(const Magic_Shooter& _Other) = delete;
	Magic_Shooter(Magic_Shooter&& _Other) noexcept = delete;
	Magic_Shooter& operator=(const Magic_Shooter& _Other) = delete;
	Magic_Shooter& operator=(Magic_Shooter&& _Other) noexcept = delete;

	//void ChangeShooterRenderer(int _TowerLevel);
	void Attack();

protected:
	void Start() override;

private:
	float4 RenderScalse = { 64, 64 };
	float Time = 0.0f;
};

