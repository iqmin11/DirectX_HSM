#pragma once
#include "BaseMonster.h"

class SandHound : public BaseMonster
{
public:
	// construtor destructor
	SandHound();
	~SandHound();

	// delete Function
	SandHound(const SandHound& _Other) = delete;
	SandHound(SandHound&& _Other) noexcept = delete;
	SandHound& operator=(const SandHound& _Other) = delete;
	SandHound& operator=(SandHound&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };
};

