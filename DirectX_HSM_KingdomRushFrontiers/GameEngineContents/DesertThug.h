#pragma once
#include "BaseMonster.h"

class DesertThug : public BaseMonster
{
public:
	// construtor destructor
	DesertThug();
	~DesertThug();

	// delete Function
	DesertThug(const DesertThug& _Other) = delete;
	DesertThug(DesertThug&& _Other) noexcept = delete;
	DesertThug& operator=(const DesertThug& _Other) = delete;
	DesertThug& operator=(DesertThug&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	float4 RenderScale = { 128,128,1 };
	float4 ColLocalPos = {0,0,0};
	float4 ColScale = {18,18,1};
};

