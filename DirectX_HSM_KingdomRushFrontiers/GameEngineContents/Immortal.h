#pragma once
#include "BaseMonster.h"

class Immortal : public BaseMonster
{
public:
	// construtor destructor
	Immortal();
	~Immortal();

	// delete Function
	Immortal(const Immortal& _Other) = delete;
	Immortal(Immortal&& _Other) noexcept = delete;
	Immortal& operator=(const Immortal& _Other) = delete;
	Immortal& operator=(Immortal&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };
};

