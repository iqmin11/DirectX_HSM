#pragma once
#include "BaseMonster.h"
class DessertArcher : public BaseMonster
{
public:
	// construtor destructor
	DessertArcher();
	~DessertArcher();

	// delete Function
	DessertArcher(const DessertArcher& _Other) = delete;
	DessertArcher(DessertArcher&& _Other) noexcept = delete;
	DessertArcher& operator=(const DessertArcher& _Other) = delete;
	DessertArcher& operator=(DessertArcher&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };
};

