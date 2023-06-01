#pragma once
#include "BaseMonster.h"

class DuneRaider : public BaseMonster
{
public:
	// construtor destructor
	DuneRaider();
	~DuneRaider();

	// delete Function
	DuneRaider(const DuneRaider& _Other) = delete;
	DuneRaider(DuneRaider&& _Other) noexcept = delete;
	DuneRaider& operator=(const DuneRaider& _Other) = delete;
	DuneRaider& operator=(DuneRaider&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = { 0,0,0 };
	float4 ColScale = { 30,30,1 };
};

