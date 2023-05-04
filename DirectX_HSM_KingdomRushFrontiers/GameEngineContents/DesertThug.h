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
	void Update(float _DeltaTime);
private:
	std::string_view TextureName = "DesertThug0000.png";
	float4 RenderScale = { 66,56 };
};

