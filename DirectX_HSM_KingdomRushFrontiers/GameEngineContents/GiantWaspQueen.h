#pragma once
#include "BaseMonster.h"
class GiantWaspQueen : public BaseMonster
{
public:
	// construtor destructor
	GiantWaspQueen();
	~GiantWaspQueen();

	// delete Function
	GiantWaspQueen(const GiantWaspQueen& _Other) = delete;
	GiantWaspQueen(GiantWaspQueen&& _Other) noexcept = delete;
	GiantWaspQueen& operator=(const GiantWaspQueen& _Other) = delete;
	GiantWaspQueen& operator=(GiantWaspQueen&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };
};

