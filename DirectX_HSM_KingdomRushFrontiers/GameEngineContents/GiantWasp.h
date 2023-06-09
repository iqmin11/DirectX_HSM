#pragma once
#include "BaseMonster.h"
class GiantWasp : public BaseMonster
{
public:
	// construtor destructor
	GiantWasp();
	~GiantWasp();

	// delete Function
	GiantWasp(const GiantWasp& _Other) = delete;
	GiantWasp(GiantWasp&& _Other) noexcept = delete;
	GiantWasp& operator=(const GiantWasp& _Other) = delete;
	GiantWasp& operator=(GiantWasp&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };
};

