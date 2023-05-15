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
	std::string_view TextureName = "DuneRaider0000.png";
	float4 RenderScale = { 60,50 };
	float4 ColScale = { 30,30 };
};

