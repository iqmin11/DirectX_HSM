#pragma once
#include "BaseMonster.h"

class WarHound : public BaseMonster
{
public:
	// construtor destructor
	WarHound();
	~WarHound();

	// delete Function
	WarHound(const WarHound& _Other) = delete;
	WarHound(WarHound&& _Other) noexcept = delete;
	WarHound& operator=(const WarHound& _Other) = delete;
	WarHound& operator=(WarHound&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };
};

