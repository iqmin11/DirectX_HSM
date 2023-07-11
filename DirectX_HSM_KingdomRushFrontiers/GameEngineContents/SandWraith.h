#pragma once
#include "BaseMonster.h"

class SandWraith : public BaseMonster
{
public:
	// construtor destructor
	SandWraith();
	~SandWraith();

	// delete Function
	SandWraith(const SandWraith& _Other) = delete;
	SandWraith(SandWraith&& _Other) noexcept = delete;
	SandWraith& operator=(const SandWraith& _Other) = delete;
	SandWraith& operator=(SandWraith&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };
};

